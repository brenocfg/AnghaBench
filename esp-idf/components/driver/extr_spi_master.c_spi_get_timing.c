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

/* Variables and functions */
 int /*<<< orphan*/  spi_hal_cal_timing (int,int,int,int*,int*) ; 

void spi_get_timing(bool gpio_is_used, int input_delay_ns, int eff_clk, int* dummy_o, int* cycles_remain_o)
{
    int timing_dummy;
    int timing_miso_delay;

    spi_hal_cal_timing(eff_clk, gpio_is_used, input_delay_ns, &timing_dummy, &timing_miso_delay);
    if (dummy_o) *dummy_o = timing_dummy;
    if (cycles_remain_o) *cycles_remain_o = timing_miso_delay;
}