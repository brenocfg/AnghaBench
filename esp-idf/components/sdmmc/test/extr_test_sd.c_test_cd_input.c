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
typedef  int /*<<< orphan*/  sdmmc_host_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  GPIO_ENABLE_W1TS_REG ; 
 int /*<<< orphan*/  GPIO_OUT_W1TC_REG ; 
 int /*<<< orphan*/  GPIO_OUT_W1TS_REG ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_GPIO_OUT_IDX ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ESP_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_matrix_out (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  sdmmc_card_init (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void test_cd_input(int gpio_cd_num, const sdmmc_host_t* config)
{
    sdmmc_card_t* card = malloc(sizeof(sdmmc_card_t));
    TEST_ASSERT_NOT_NULL(card);

    // SDMMC host should have configured CD as input.
    // Enable output as well (not using the driver, to avoid touching input
    // enable bits).
    gpio_matrix_out(gpio_cd_num, SIG_GPIO_OUT_IDX, false, false);
    REG_WRITE(GPIO_ENABLE_W1TS_REG, BIT(gpio_cd_num));

    // Check that card initialization fails if CD is high
    REG_WRITE(GPIO_OUT_W1TS_REG, BIT(gpio_cd_num));
    usleep(1000);
    TEST_ESP_ERR(ESP_ERR_NOT_FOUND, sdmmc_card_init(config, card));

    // Check that card initialization succeeds if CD is low
    REG_WRITE(GPIO_OUT_W1TC_REG, BIT(gpio_cd_num));
    usleep(1000);
    TEST_ESP_OK(sdmmc_card_init(config, card));

    free(card);
}