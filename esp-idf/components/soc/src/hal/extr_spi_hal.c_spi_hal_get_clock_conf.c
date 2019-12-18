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
struct TYPE_5__ {scalar_t__ timing_dummy; int /*<<< orphan*/  timing_miso_delay; int /*<<< orphan*/  clock_reg; } ;
typedef  TYPE_1__ spi_hal_timing_conf_t ;
struct TYPE_6__ {scalar_t__ no_compensate; scalar_t__ half_duplex; } ;
typedef  TYPE_2__ spi_hal_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  APB_CLK_FREQ ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SPI_HAL_CHECK (int,char*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  spi_hal_cal_timing (int,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int spi_hal_get_freq_limit (int,int) ; 
 int spi_ll_master_cal_clock (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

esp_err_t spi_hal_get_clock_conf(const spi_hal_context_t *hal, int speed_hz, int duty_cycle, bool use_gpio, int input_delay_ns, int *out_freq, spi_hal_timing_conf_t *timing_conf)
{
    spi_hal_timing_conf_t temp_conf;

    int eff_clk_n = spi_ll_master_cal_clock(APB_CLK_FREQ, speed_hz, duty_cycle, &temp_conf.clock_reg);

    //When the speed is too fast, we may need to use dummy cycles to compensate the reading.
    //But these don't work for full-duplex connections.
    spi_hal_cal_timing(eff_clk_n, use_gpio, input_delay_ns, &temp_conf.timing_dummy, &temp_conf.timing_miso_delay);

#ifdef CONFIG_IDF_TARGET_ESP32
    const int freq_limit = spi_hal_get_freq_limit(use_gpio, input_delay_ns);

    SPI_HAL_CHECK(hal->half_duplex || temp_conf.timing_dummy == 0 || hal->no_compensate,
                  "When work in full-duplex mode at frequency > %.1fMHz, device cannot read correct data.\n\
Try to use IOMUX pins to increase the frequency limit, or use the half duplex mode.\n\
Please note the SPI master can only work at divisors of 80MHz, and the driver always tries to find the closest frequency to your configuration.\n\
Specify ``SPI_DEVICE_NO_DUMMY`` to ignore this checking. Then you can output data at higher speed, or read data at your own risk.",
                  ESP_ERR_NOT_SUPPORTED, freq_limit / 1000. / 1000 );
#endif

    if (timing_conf) {
        *timing_conf = temp_conf;
    }
    if (out_freq) {
        *out_freq = eff_clk_n;
    }
    return ESP_OK;
}