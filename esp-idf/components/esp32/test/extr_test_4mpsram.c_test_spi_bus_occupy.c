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
typedef  scalar_t__ spi_host_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ HSPI_HOST ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_FALSE (int) ; 
 scalar_t__ VSPI_HOST ; 
 int spicommon_periph_claim (scalar_t__,char*) ; 
 int /*<<< orphan*/  test_psram_content () ; 

__attribute__((used)) static void test_spi_bus_occupy(spi_host_device_t expected_occupied_host)
{
    bool claim_hspi = spicommon_periph_claim(HSPI_HOST, "ut-hspi");
    if (claim_hspi) ESP_LOGI(TAG, "HSPI claimed.");

    bool claim_vspi = spicommon_periph_claim(VSPI_HOST, "ut-vspi");
    if (claim_vspi) ESP_LOGI(TAG, "VSPI claimed.");

    if (expected_occupied_host == HSPI_HOST) {
        TEST_ASSERT_FALSE(claim_hspi);
        TEST_ASSERT(claim_vspi);
    } else if (expected_occupied_host == VSPI_HOST) {
        TEST_ASSERT_FALSE(claim_vspi);
        TEST_ASSERT(claim_hspi);
    } else {
        TEST_ASSERT(claim_hspi);
        TEST_ASSERT(claim_vspi);
    }

#ifdef CONFIG_SPIRAM
    test_psram_content();
#endif
}