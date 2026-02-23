#include "opus.h"
#include "esp_log.h"
#include <stddef.h>

static const char *TAG = "opus_ci";

void app_main(void)
{
    int err = 0;
    OpusEncoder *enc = opus_encoder_create(16000, 1, OPUS_APPLICATION_VOIP, &err);
    if (enc == NULL) {
        ESP_LOGE(TAG, "opus_encoder_create failed: %d", err);
        return;
    }
    opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(5));

    int frame_size = 960;
    int16_t pcm[960];
    uint8_t opus_buf[1500];
    int len = opus_encode(enc, pcm, frame_size, opus_buf, sizeof(opus_buf));
    opus_encoder_destroy(enc);

    if (len > 0) {
        ESP_LOGI(TAG, "opus encode ok, len=%d", len);
    } else {
        ESP_LOGE(TAG, "opus_encode failed: %d", len);
    }
}
