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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sdmmc_host_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  GPIO_ENABLE_W1TS_REG ; 
 int /*<<< orphan*/  GPIO_OUT_W1TC_REG ; 
 int /*<<< orphan*/  GPIO_OUT_W1TS_REG ; 
 int /*<<< orphan*/  MALLOC_CAP_DMA ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_GPIO_OUT_IDX ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ESP_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_matrix_out (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * heap_caps_calloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  sdmmc_card_init (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_read_sectors (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdmmc_write_sectors (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void test_wp_input(int gpio_wp_num, const sdmmc_host_t* config)
{
    sdmmc_card_t* card = malloc(sizeof(sdmmc_card_t));
    TEST_ASSERT_NOT_NULL(card);

    // SDMMC host should have configured WP as input.
    // Enable output as well (not using the driver, to avoid touching input
    // enable bits).
    gpio_matrix_out(gpio_wp_num, SIG_GPIO_OUT_IDX, false, false);
    REG_WRITE(GPIO_ENABLE_W1TS_REG, BIT(gpio_wp_num));

    // Check that the card can be initialized with WP low
    REG_WRITE(GPIO_OUT_W1TC_REG, BIT(gpio_wp_num));
    TEST_ESP_OK(sdmmc_card_init(config, card));

    uint32_t* data = heap_caps_calloc(1, 512, MALLOC_CAP_DMA);

    // Check that card write succeeds if WP is high
    REG_WRITE(GPIO_OUT_W1TS_REG, BIT(gpio_wp_num));
    usleep(1000);
    TEST_ESP_OK(sdmmc_write_sectors(card, &data, 0, 1));

    // Check that write fails if WP is low
    REG_WRITE(GPIO_OUT_W1TC_REG, BIT(gpio_wp_num));
    usleep(1000);
    TEST_ESP_ERR(ESP_ERR_INVALID_STATE, sdmmc_write_sectors(card, &data, 0, 1));
    // ...but reads still work
    TEST_ESP_OK(sdmmc_read_sectors(card, &data, 0, 1));

    free(data);
    free(card);
}