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
typedef  scalar_t__ spi_host_device_t ;
struct TYPE_3__ {int quadhd_io_num; int max_transfer_sz; int /*<<< orphan*/  quadwp_io_num; int /*<<< orphan*/  sclk_io_num; int /*<<< orphan*/  miso_io_num; int /*<<< orphan*/  mosi_io_num; } ;
typedef  TYPE_1__ spi_bus_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXTRA_SPI1_CLK_IO ; 
 scalar_t__ HSPI_HOST ; 
 int /*<<< orphan*/  HSPI_PIN_NUM_CLK ; 
 int HSPI_PIN_NUM_HD ; 
 int /*<<< orphan*/  HSPI_PIN_NUM_MISO ; 
 int /*<<< orphan*/  HSPI_PIN_NUM_MOSI ; 
 int /*<<< orphan*/  HSPI_PIN_NUM_WP ; 
 int /*<<< orphan*/  SPICLK_OUT_IDX ; 
 scalar_t__ SPI_HOST ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 scalar_t__ VSPI_HOST ; 
 int /*<<< orphan*/  VSPI_PIN_NUM_CLK ; 
 int VSPI_PIN_NUM_HD ; 
 int /*<<< orphan*/  VSPI_PIN_NUM_MISO ; 
 int /*<<< orphan*/  VSPI_PIN_NUM_MOSI ; 
 int /*<<< orphan*/  VSPI_PIN_NUM_WP ; 
 int /*<<< orphan*/  gpio_matrix_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_initialize (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_bus(spi_host_device_t host_id)
{
    if (host_id == SPI_HOST) {
        ESP_LOGI(TAG, "setup flash on SPI1 CS1...\n");
        //no need to initialize the bus, however the CLK may need one more output if it's on the usual place of PSRAM
#ifdef EXTRA_SPI1_CLK_IO
        gpio_matrix_out(EXTRA_SPI1_CLK_IO, SPICLK_OUT_IDX, 0, 0);
#endif
        //currently the SPI bus for main flash chip is initialized through GPIO matrix
    } else if (host_id == HSPI_HOST) {
        ESP_LOGI(TAG, "setup flash on SPI2 (HSPI) CS0...\n");
        spi_bus_config_t hspi_bus_cfg = {
            .mosi_io_num = HSPI_PIN_NUM_MOSI,
            .miso_io_num = HSPI_PIN_NUM_MISO,
            .sclk_io_num = HSPI_PIN_NUM_CLK,
            .quadhd_io_num = HSPI_PIN_NUM_HD,
            .quadwp_io_num = HSPI_PIN_NUM_WP,
            .max_transfer_sz = 64,
        };
#ifdef FORCE_GPIO_MATRIX
        hspi_bus_cfg.quadhd_io_num = 23;
#endif
        esp_err_t ret = spi_bus_initialize(host_id, &hspi_bus_cfg, 0);
        TEST_ESP_OK(ret);
    } else if (host_id == VSPI_HOST) {
        ESP_LOGI(TAG, "setup flash on SPI3 (VSPI) CS0...\n");
        spi_bus_config_t vspi_bus_cfg = {
            .mosi_io_num = VSPI_PIN_NUM_MOSI,
            .miso_io_num = VSPI_PIN_NUM_MISO,
            .sclk_io_num = VSPI_PIN_NUM_CLK,
            .quadhd_io_num = VSPI_PIN_NUM_HD,
            .quadwp_io_num = VSPI_PIN_NUM_WP,
            .max_transfer_sz = 64,
        };
#ifdef FORCE_GPIO_MATRIX
        vspi_bus_cfg.quadhd_io_num = 23;
#endif
        esp_err_t ret = spi_bus_initialize(host_id, &vspi_bus_cfg, 0);
        TEST_ESP_OK(ret);
    } else {
        ESP_LOGE(TAG, "invalid bus");
    }
}