#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int gpio_miso; int gpio_mosi; int gpio_sck; int gpio_cs; } ;
typedef  TYPE_1__ sdspi_slot_config_t ;
struct TYPE_8__ {int /*<<< orphan*/  slot; } ;
typedef  TYPE_2__ sdmmc_host_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;

/* Variables and functions */
 TYPE_2__ SDSPI_HOST_DEFAULT () ; 
 TYPE_1__ SDSPI_SLOT_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  sd_test_board_power_off () ; 
 int /*<<< orphan*/  sd_test_board_power_on () ; 
 int /*<<< orphan*/  sdmmc_card_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_card_print_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdspi_host_deinit () ; 
 int /*<<< orphan*/  sdspi_host_init () ; 
 int /*<<< orphan*/  sdspi_host_init_slot (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void probe_spi(int freq_khz, int pin_miso, int pin_mosi, int pin_sck, int pin_cs)
{
    sd_test_board_power_on();
    sdmmc_host_t config = SDSPI_HOST_DEFAULT();
    sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
    slot_config.gpio_miso = pin_miso;
    slot_config.gpio_mosi = pin_mosi;
    slot_config.gpio_sck = pin_sck;
    slot_config.gpio_cs = pin_cs;

    TEST_ESP_OK(sdspi_host_init());
    TEST_ESP_OK(sdspi_host_init_slot(config.slot, &slot_config));
    sdmmc_card_t* card = malloc(sizeof(sdmmc_card_t));
    TEST_ASSERT_NOT_NULL(card);
    TEST_ESP_OK(sdmmc_card_init(&config, card));
    sdmmc_card_print_info(stdout, card);
    TEST_ESP_OK(sdspi_host_deinit());
    free(card);
    sd_test_board_power_off();
}