#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ adc2_channel_t ;

/* Variables and functions */
 scalar_t__ ADC2_CHANNEL_6 ; 
 scalar_t__ ADC2_CHANNEL_7 ; 
 scalar_t__ ADC2_CHANNEL_8 ; 
 scalar_t__ ADC2_CHANNEL_9 ; 
 int /*<<< orphan*/  DAC_CHANNEL_1 ; 
 int /*<<< orphan*/  DAC_CHANNEL_2 ; 
 int /*<<< orphan*/  dac_output_set_enable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void adc2_dac_disable( adc2_channel_t channel)
{
#if CONFIG_IDF_TARGET_ESP32
    if ( channel == ADC2_CHANNEL_8 ) { // the same as DAC channel 1
        dac_output_set_enable( DAC_CHANNEL_1, false );
    } else if ( channel == ADC2_CHANNEL_9 ) {
        dac_output_set_enable( DAC_CHANNEL_2, false );
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    if ( channel == ADC2_CHANNEL_6 ) { // the same as DAC channel 1
        dac_output_set_enable( DAC_CHANNEL_1, false );
    } else if ( channel == ADC2_CHANNEL_7 ) {
        dac_output_set_enable( DAC_CHANNEL_2, false );
    }
#endif
}