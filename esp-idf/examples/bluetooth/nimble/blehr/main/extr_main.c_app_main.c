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
typedef  scalar_t__ esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/  reset_cb; int /*<<< orphan*/  sync_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (scalar_t__) ; 
 scalar_t__ ESP_ERR_NVS_NEW_VERSION_FOUND ; 
 scalar_t__ ESP_ERR_NVS_NO_FREE_PAGES ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ ble_hs_cfg ; 
 int ble_svc_gap_device_name_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blehr_host_task ; 
 int /*<<< orphan*/  blehr_on_reset ; 
 int /*<<< orphan*/  blehr_on_sync ; 
 int /*<<< orphan*/  blehr_tx_hrate ; 
 int /*<<< orphan*/  blehr_tx_timer ; 
 int /*<<< orphan*/  device_name ; 
 scalar_t__ esp_nimble_hci_and_controller_init () ; 
 int gatt_svr_init () ; 
 int /*<<< orphan*/  nimble_port_freertos_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nimble_port_init () ; 
 scalar_t__ nvs_flash_erase () ; 
 scalar_t__ nvs_flash_init () ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int /*<<< orphan*/  pdTRUE ; 
 int /*<<< orphan*/  xTimerCreate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void app_main(void)
{
    int rc;

    /* Initialize NVS — it is used to store PHY calibration data */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_nimble_hci_and_controller_init());

    nimble_port_init();
    /* Initialize the NimBLE host configuration */
    ble_hs_cfg.sync_cb = blehr_on_sync;
    ble_hs_cfg.reset_cb = blehr_on_reset;

    /* name, period/time,  auto reload, timer ID, callback */
    blehr_tx_timer = xTimerCreate("blehr_tx_timer", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, blehr_tx_hrate);

    rc = gatt_svr_init();
    assert(rc == 0);

    /* Set the default device name */
    rc = ble_svc_gap_device_name_set(device_name);
    assert(rc == 0);

    /* Start the task */
    nimble_port_freertos_init(blehr_host_task);

}