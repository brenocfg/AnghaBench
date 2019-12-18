#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ simple_ble_cfg_t ;
struct TYPE_8__ {int /*<<< orphan*/  gatts_register_cb; int /*<<< orphan*/  sync_cb; int /*<<< orphan*/  reset_cb; } ;
struct TYPE_7__ {int name_is_complete; int /*<<< orphan*/  name_len; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 void* ble_cfg_p ; 
 TYPE_5__ ble_hs_cfg ; 
 int /*<<< orphan*/  ble_store_config_init () ; 
 scalar_t__ ble_svc_gap_device_name () ; 
 int ble_svc_gap_device_name_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_get_free_heap_size () ; 
 int /*<<< orphan*/  esp_nimble_hci_and_controller_init () ; 
 int gatt_svr_init (TYPE_1__ const*) ; 
 int /*<<< orphan*/  gatt_svr_register_cb ; 
 int /*<<< orphan*/  nimble_host_task ; 
 int /*<<< orphan*/  nimble_port_freertos_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nimble_port_init () ; 
 TYPE_3__ resp_data ; 
 int /*<<< orphan*/  simple_ble_on_reset ; 
 int /*<<< orphan*/  simple_ble_on_sync ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static int simple_ble_start(const simple_ble_cfg_t *cfg)
{
    ble_cfg_p = (void *)cfg;
    int rc;
    ESP_LOGD(TAG, "Free mem at start of simple_ble_init %d", esp_get_free_heap_size());

    ESP_ERROR_CHECK(esp_nimble_hci_and_controller_init());
    nimble_port_init();

    /* Initialize the NimBLE host configuration. */
    ble_hs_cfg.reset_cb = simple_ble_on_reset;
    ble_hs_cfg.sync_cb = simple_ble_on_sync;
    ble_hs_cfg.gatts_register_cb = gatt_svr_register_cb;

    rc = gatt_svr_init(cfg);
    if (rc != 0) {
        ESP_LOGE(TAG, "Error initializing GATT server");
        return rc;
    }

    /* Set device name, configure response data to be sent while advertising */
    rc = ble_svc_gap_device_name_set(cfg->device_name);
    if (rc != 0) {
        ESP_LOGE(TAG, "Error setting device name");
        return rc;
    }

    resp_data.name = (void *) ble_svc_gap_device_name();
    if (resp_data.name != NULL) {
        resp_data.name_len = strlen(ble_svc_gap_device_name());
        resp_data.name_is_complete = 1;
    }

    /* XXX Need to have template for store */
    ble_store_config_init();
    nimble_port_freertos_init(nimble_host_task);

    return 0;
}