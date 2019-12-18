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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int width; } ;
typedef  TYPE_1__ sdmmc_slot_config_t ;
struct TYPE_8__ {int slot; int max_freq_khz; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ sdmmc_host_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;

/* Variables and functions */
 int /*<<< orphan*/  MALLOC_CAP_DMA ; 
 TYPE_2__ SDMMC_HOST_DEFAULT () ; 
 int /*<<< orphan*/  SDMMC_HOST_FLAG_1BIT ; 
 int /*<<< orphan*/  SDMMC_HOST_FLAG_8BIT ; 
 int /*<<< orphan*/  SDMMC_HOST_FLAG_DDR ; 
 TYPE_1__ SDMMC_SLOT_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_caps_malloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  sd_test_board_power_off () ; 
 int /*<<< orphan*/  sd_test_board_power_on () ; 
 int /*<<< orphan*/  sdmmc_card_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_card_print_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_host_deinit () ; 
 int /*<<< orphan*/  sdmmc_host_init () ; 
 int /*<<< orphan*/  sdmmc_host_init_slot (int,TYPE_1__*) ; 
 int /*<<< orphan*/  sdmmc_read_sectors (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void probe_sd(int slot, int width, int freq_khz, int ddr)
{
    sd_test_board_power_on();
    sdmmc_host_t config = SDMMC_HOST_DEFAULT();
    config.slot = slot;
    config.max_freq_khz = freq_khz;
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    if (width == 1) {
        config.flags = SDMMC_HOST_FLAG_1BIT;
        slot_config.width = 1;
    } else if (width == 4) {
        config.flags &= ~SDMMC_HOST_FLAG_8BIT;
        slot_config.width = 4;
    } else {
        assert(!ddr && "host driver does not support 8-line DDR mode yet");
    }
    if (!ddr) {
        config.flags &= ~SDMMC_HOST_FLAG_DDR;
    }
    TEST_ESP_OK(sdmmc_host_init());
    TEST_ESP_OK(sdmmc_host_init_slot(slot, &slot_config));
    sdmmc_card_t* card = malloc(sizeof(sdmmc_card_t));
    TEST_ASSERT_NOT_NULL(card);
    TEST_ESP_OK(sdmmc_card_init(&config, card));
    sdmmc_card_print_info(stdout, card);
    uint8_t* buffer = heap_caps_malloc(512, MALLOC_CAP_DMA);
    TEST_ESP_OK(sdmmc_read_sectors(card, buffer, 0, 1));
    free(buffer);
    TEST_ESP_OK(sdmmc_host_deinit());
    free(card);
    sd_test_board_power_off();
}