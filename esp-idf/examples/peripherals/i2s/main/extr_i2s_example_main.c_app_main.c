#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data_in_num; int /*<<< orphan*/  data_out_num; int /*<<< orphan*/  ws_io_num; int /*<<< orphan*/  bck_io_num; } ;
typedef  TYPE_1__ i2s_pin_config_t ;
struct TYPE_6__ {int mode; int bits_per_sample; int communication_format; int dma_buf_count; int dma_buf_len; int use_apll; int /*<<< orphan*/  intr_alloc_flags; int /*<<< orphan*/  channel_format; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_2__ i2s_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_INTR_FLAG_LEVEL1 ; 
 int /*<<< orphan*/  I2S_BCK_IO ; 
 int /*<<< orphan*/  I2S_CHANNEL_FMT_RIGHT_LEFT ; 
 int I2S_COMM_FORMAT_I2S ; 
 int I2S_COMM_FORMAT_I2S_MSB ; 
 int /*<<< orphan*/  I2S_DI_IO ; 
 int /*<<< orphan*/  I2S_DO_IO ; 
 int I2S_MODE_MASTER ; 
 int I2S_MODE_TX ; 
 int /*<<< orphan*/  I2S_NUM ; 
 int /*<<< orphan*/  I2S_WS_IO ; 
 int /*<<< orphan*/  SAMPLE_RATE ; 
 int /*<<< orphan*/  i2s_driver_install (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2s_set_pin (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  setup_triangle_sine_waves (int) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void app_main(void)
{
    //for 36Khz sample rates, we create 100Hz sine wave, every cycle need 36000/100 = 360 samples (4-bytes or 8-bytes each sample)
    //depend on bits_per_sample
    //using 6 buffers, we need 60-samples per buffer
    //if 2-channels, 16-bit each channel, total buffer is 360*4 = 1440 bytes
    //if 2-channels, 24/32-bit each channel, total buffer is 360*8 = 2880 bytes
    i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,                                  // Only TX
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = 16,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           //2-channels
        .communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
        .dma_buf_count = 6,
        .dma_buf_len = 60,
        .use_apll = false,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1                                //Interrupt level 1
    };
    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCK_IO,
        .ws_io_num = I2S_WS_IO,
        .data_out_num = I2S_DO_IO,
        .data_in_num = I2S_DI_IO                                               //Not used
    };
    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);

    int test_bits = 16;
    while (1) {
        setup_triangle_sine_waves(test_bits);
        vTaskDelay(5000/portTICK_RATE_MS);
        test_bits += 8;
        if(test_bits > 32)
            test_bits = 16;

    }

}