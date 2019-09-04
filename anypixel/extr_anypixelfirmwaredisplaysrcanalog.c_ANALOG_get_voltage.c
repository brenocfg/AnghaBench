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
typedef  int uint16_t ;

/* Variables and functions */
 int ADC_PINS_NUM ; 
 int* adc_readings ; 

uint16_t ANALOG_get_voltage(int channel) {
    if(channel < ADC_PINS_NUM)
        return adc_readings[channel];
    else
        return 0xFFFF;
}