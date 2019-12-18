#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t spi_host_device_t ;
struct TYPE_2__ {int spics0_iomux_pin; int /*<<< orphan*/  spics_in; int /*<<< orphan*/ * spics_out; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_GPIO ; 
 scalar_t__ GPIO_IS_VALID_OUTPUT_GPIO (int) ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT_OUTPUT ; 
 int /*<<< orphan*/ * GPIO_PIN_MUX_REG ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIN_INPUT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_iomux_in (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_iomux_out (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_matrix_in (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_matrix_out (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gpio_set_direction (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* spi_periph_signal ; 

void spicommon_cs_initialize(spi_host_device_t host, int cs_io_num, int cs_num, int force_gpio_matrix)
{
    if (!force_gpio_matrix && cs_io_num == spi_periph_signal[host].spics0_iomux_pin && cs_num == 0) {
        //The cs0s for all SPI peripherals map to pin mux source 1, so we use that instead of a define.
        gpio_iomux_in(cs_io_num, spi_periph_signal[host].spics_in);
#if CONFIG_IDF_TARGET_ESP32
        gpio_iomux_out(cs_io_num, spi_periph_signal[host].func, false);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
        gpio_iomux_out(cs_io_num, spi_periph_signal[host].func, false);
#endif
    } else {
        //Use GPIO matrix
        if (GPIO_IS_VALID_OUTPUT_GPIO(cs_io_num)) {
            gpio_set_direction(cs_io_num, GPIO_MODE_INPUT_OUTPUT);
            gpio_matrix_out(cs_io_num, spi_periph_signal[host].spics_out[cs_num], false, false);
        } else {
            gpio_set_direction(cs_io_num, GPIO_MODE_INPUT);
        }
        if (cs_num == 0) gpio_matrix_in(cs_io_num, spi_periph_signal[host].spics_in, false);
        PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[cs_io_num]);
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[cs_io_num], FUNC_GPIO);
    }
}