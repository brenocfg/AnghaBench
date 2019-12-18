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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NVS_NEW_VERSION_FOUND ; 
 scalar_t__ ESP_ERR_NVS_NO_FREE_PAGES ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PHY_BT_MODULE ; 
 int /*<<< orphan*/  PHY_WIFI_MODULE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (scalar_t__) ; 
 int /*<<< orphan*/  esp_phy_load_cal_and_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvs_flash_deinit () ; 
 scalar_t__ nvs_flash_erase () ; 
 scalar_t__ nvs_flash_init () ; 

__attribute__((used)) static void test_phy_rtc_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGI(TAG, "no free pages or nvs version mismatch, erase..");
        TEST_ESP_OK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    TEST_ESP_OK(ret);

#ifdef SOC_BT_SUPPORTED
    esp_phy_load_cal_and_init(PHY_BT_MODULE);
#endif
    esp_phy_load_cal_and_init(PHY_WIFI_MODULE);

    //must run here, not blocking in above code
    TEST_ASSERT(1);
    nvs_flash_deinit();
}