#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; int dma_buf_count; int dma_buf_len; int use_apll; int /*<<< orphan*/  intr_alloc_flags; int /*<<< orphan*/  channel_format; int /*<<< orphan*/  communication_format; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_1__ i2s_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXAMPLE_I2S_FORMAT ; 
 int EXAMPLE_I2S_NUM ; 
 int /*<<< orphan*/  EXAMPLE_I2S_SAMPLE_BITS ; 
 int /*<<< orphan*/  EXAMPLE_I2S_SAMPLE_RATE ; 
 int /*<<< orphan*/  I2S_ADC_CHANNEL ; 
 int /*<<< orphan*/  I2S_ADC_UNIT ; 
 int /*<<< orphan*/  I2S_COMM_FORMAT_I2S_MSB ; 
 int /*<<< orphan*/  I2S_DAC_CHANNEL_BOTH_EN ; 
 int I2S_MODE_ADC_BUILT_IN ; 
 int I2S_MODE_DAC_BUILT_IN ; 
 int I2S_MODE_MASTER ; 
 int I2S_MODE_RX ; 
 int I2S_MODE_TX ; 
 int /*<<< orphan*/  i2s_driver_install (int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2s_set_adc_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_set_dac_mode (int /*<<< orphan*/ ) ; 

void example_i2s_init(void)
{
	 int i2s_num = EXAMPLE_I2S_NUM;
	 i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN | I2S_MODE_ADC_BUILT_IN,
        .sample_rate =  EXAMPLE_I2S_SAMPLE_RATE,
        .bits_per_sample = EXAMPLE_I2S_SAMPLE_BITS,
	    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
	    .channel_format = EXAMPLE_I2S_FORMAT,
	    .intr_alloc_flags = 0,
	    .dma_buf_count = 2,
	    .dma_buf_len = 1024,
	    .use_apll = 1,
	 };
	 //install and start i2s driver
	 i2s_driver_install(i2s_num, &i2s_config, 0, NULL);
	 //init DAC pad
	 i2s_set_dac_mode(I2S_DAC_CHANNEL_BOTH_EN);
	 //init ADC pad
	 i2s_set_adc_mode(I2S_ADC_UNIT, I2S_ADC_CHANNEL);
}