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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ets_delay_us (int) ; 
 int /*<<< orphan*/  gpio_output_set_high (int /*<<< orphan*/ ,int const,int const,int const) ; 
 int /*<<< orphan*/  gpio_pad_select_gpio (int const) ; 
 int /*<<< orphan*/  rtc_clk_32k_enable (int) ; 

void stop_rtc_external_quartz(void){
    const uint8_t pin_32 = 32;
    const uint8_t pin_33 = 33;
    const uint8_t mask_32 = (1 << (pin_32 - 32));
    const uint8_t mask_33 = (1 << (pin_33 - 32));

    rtc_clk_32k_enable(false);

    gpio_pad_select_gpio(pin_32);
    gpio_pad_select_gpio(pin_33);
    gpio_output_set_high(0, mask_32 | mask_33, mask_32 | mask_33, 0);
    ets_delay_us(500000);
    gpio_output_set_high(0, 0, 0, mask_32 | mask_33); // disable pins
}