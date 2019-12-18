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
struct TYPE_5__ {int host_id; int /*<<< orphan*/  input_delay_ns; int /*<<< orphan*/  cs_io_num; int /*<<< orphan*/  cs_id; int /*<<< orphan*/  speed; int /*<<< orphan*/  io_mode; } ;
typedef  TYPE_1__ flashtest_config_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;
struct TYPE_6__ {int host_id; int /*<<< orphan*/  input_delay_ns; int /*<<< orphan*/  cs_io_num; int /*<<< orphan*/  cs_id; int /*<<< orphan*/  speed; int /*<<< orphan*/  io_mode; } ;
typedef  TYPE_2__ esp_flash_spi_device_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_flash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_bus (int) ; 
 int /*<<< orphan*/  spi_bus_add_flash_device (int /*<<< orphan*/ **,TYPE_2__*) ; 

__attribute__((used)) static void setup_new_chip(const flashtest_config_t* test_cfg, esp_flash_t** out_chip)
{
    //the bus should be initialized before the flash is attached to the bus
    if (test_cfg->host_id == -1) {
        *out_chip = NULL;
        return;
    }
    setup_bus(test_cfg->host_id);

    esp_flash_spi_device_config_t dev_cfg = {
        .host_id = test_cfg->host_id,
        .io_mode = test_cfg->io_mode,
        .speed = test_cfg->speed,
        .cs_id = test_cfg->cs_id,
        .cs_io_num = test_cfg->cs_io_num,
        .input_delay_ns = test_cfg->input_delay_ns,
    };
    esp_flash_t* init_chip;
    esp_err_t err = spi_bus_add_flash_device(&init_chip, &dev_cfg);
    TEST_ESP_OK(err);
    err = esp_flash_init(init_chip);
    TEST_ESP_OK(err);
    *out_chip = init_chip;
}