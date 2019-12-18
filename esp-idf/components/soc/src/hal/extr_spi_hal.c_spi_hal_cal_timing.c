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
 int APB_CLK_FREQ ; 
 int GPIO_MATRIX_DELAY_NS ; 
 int /*<<< orphan*/  HAL_LOGD (int /*<<< orphan*/ ,char*,int,int const,int,int,int) ; 
 int /*<<< orphan*/  SPI_HAL_TAG ; 

void spi_hal_cal_timing(int eff_clk, bool gpio_is_used, int input_delay_ns, int *dummy_n, int *miso_delay_n)
{
    const int apbclk_kHz = APB_CLK_FREQ / 1000;
    //calculate how many apb clocks a period has
    const int apbclk_n = APB_CLK_FREQ / eff_clk;
    const int gpio_delay_ns = gpio_is_used ? GPIO_MATRIX_DELAY_NS : 0;

    //calculate how many apb clocks the delay is, the 1 is to compensate in case ``input_delay_ns`` is rounded off.
    int apb_period_n = (1 + input_delay_ns + gpio_delay_ns) * apbclk_kHz / 1000 / 1000;
    if (apb_period_n < 0) {
        apb_period_n = 0;
    }

    int dummy_required = apb_period_n / apbclk_n;

    int miso_delay = 0;
    if (dummy_required > 0) {
        //due to the clock delay between master and slave, there's a range in which data is random
        //give MISO a delay if needed to make sure we sample at the time MISO is stable
        miso_delay = (dummy_required + 1) * apbclk_n - apb_period_n - 1;
    } else {
        //if the dummy is not required, maybe we should also delay half a SPI clock if the data comes too early
        if (apb_period_n * 4 <= apbclk_n) {
            miso_delay = -1;
        }
    }
    *dummy_n = dummy_required;
    *miso_delay_n = miso_delay;
    HAL_LOGD(SPI_HAL_TAG, "eff: %d, limit: %dk(/%d), %d dummy, %d delay", eff_clk / 1000, apbclk_kHz / (apb_period_n + 1), apb_period_n, dummy_required, miso_delay);
}