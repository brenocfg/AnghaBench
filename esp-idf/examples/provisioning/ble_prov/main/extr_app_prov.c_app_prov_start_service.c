#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {char* member_0; int member_1; } ;
typedef  TYPE_1__ protocomm_ble_name_uuid_t ;
struct TYPE_6__ {int nu_lookup_count; int /*<<< orphan*/  device_name; TYPE_1__* nu_lookup; int /*<<< orphan*/  service_uuid; } ;
typedef  TYPE_2__ protocomm_ble_config_t ;
typedef  int /*<<< orphan*/  nu_lookup_table ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_7__ {int security; int /*<<< orphan*/ * pc; int /*<<< orphan*/ * pop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BT_MODE_CLASSIC_BT ; 
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WIFI_IF_STA ; 
 scalar_t__ esp_bt_controller_mem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wifi_get_mac (int /*<<< orphan*/ ,int*) ; 
 TYPE_4__* g_prov ; 
 scalar_t__ protocomm_add_endpoint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ protocomm_ble_start (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  protocomm_ble_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * protocomm_new () ; 
 int /*<<< orphan*/  protocomm_security0 ; 
 int /*<<< orphan*/  protocomm_security1 ; 
 int /*<<< orphan*/  protocomm_set_security (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  protocomm_set_version (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int,int,int) ; 
 char* ssid_prefix ; 
 int /*<<< orphan*/  wifi_prov_config_data_handler ; 
 int /*<<< orphan*/  wifi_prov_handlers ; 

__attribute__((used)) static esp_err_t app_prov_start_service(void)
{
    /* Create new protocomm instance */
    g_prov->pc = protocomm_new();
    if (g_prov->pc == NULL) {
        ESP_LOGE(TAG, "Failed to create new protocomm instance");
        return ESP_FAIL;
    }

    /* Endpoint UUIDs */
    protocomm_ble_name_uuid_t nu_lookup_table[] = {
        {"prov-session", 0x0001},
        {"prov-config",  0x0002},
        {"proto-ver",    0x0003},
    };

    /* Config for protocomm_ble_start() */
    protocomm_ble_config_t config = {
        .service_uuid = {
            /* LSB <---------------------------------------
             * ---------------------------------------> MSB */
            0xb4, 0xdf, 0x5a, 0x1c, 0x3f, 0x6b, 0xf4, 0xbf,
            0xea, 0x4a, 0x82, 0x03, 0x04, 0x90, 0x1a, 0x02,
        },
        .nu_lookup_count = sizeof(nu_lookup_table)/sizeof(nu_lookup_table[0]),
        .nu_lookup = nu_lookup_table
    };

    /* With the above selection of 128bit primary service UUID and
     * 16bit endpoint UUIDs, the 128bit characteristic UUIDs will be
     * formed by replacing the 12th and 13th bytes of the service UUID
     * with the 16bit endpoint UUID, i.e. :
     *    service UUID : 021a9004-0382-4aea-bff4-6b3f1c5adfb4
     *     masked base : 021a____-0382-4aea-bff4-6b3f1c5adfb4
     * ------------------------------------------------------
     * resulting characteristic UUIDs :
     * 1) prov-session : 021a0001-0382-4aea-bff4-6b3f1c5adfb4
     * 2)  prov-config : 021a0002-0382-4aea-bff4-6b3f1c5adfb4
     * 3)    proto-ver : 021a0003-0382-4aea-bff4-6b3f1c5adfb4
     *
     * Also, note that each endpoint (characteristic) will have
     * an associated "Characteristic User Description" descriptor
     * with 16bit UUID 0x2901, each containing the corresponding
     * endpoint name. These descriptors can be used by a client
     * side application to figure out which characteristic is
     * mapped to which endpoint, without having to hardcode the
     * UUIDs */

    uint8_t eth_mac[6];
    esp_wifi_get_mac(WIFI_IF_STA, eth_mac);
    snprintf(config.device_name, sizeof(config.device_name), "%s%02X%02X%02X",
             ssid_prefix, eth_mac[3], eth_mac[4], eth_mac[5]);

    /* Release BT memory, as we need only BLE */
    esp_err_t err = esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
    if (err) {
        ESP_LOGE(TAG, "bt_controller_mem_release failed %d", err);
        if (err != ESP_ERR_INVALID_STATE) {
            return err;
        }
    }

    /* Start protocomm layer on top of BLE */
    if (protocomm_ble_start(g_prov->pc, &config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start BLE provisioning");
        return ESP_FAIL;
    }

    /* Set protocomm version verification endpoint for protocol */
    protocomm_set_version(g_prov->pc, "proto-ver", "V0.1");

    /* Set protocomm security type for endpoint */
    if (g_prov->security == 0) {
        protocomm_set_security(g_prov->pc, "prov-session", &protocomm_security0, NULL);
    } else if (g_prov->security == 1) {
        protocomm_set_security(g_prov->pc, "prov-session", &protocomm_security1, g_prov->pop);
    }

    /* Add endpoint for provisioning to set wifi station config */
    if (protocomm_add_endpoint(g_prov->pc, "prov-config",
                               wifi_prov_config_data_handler,
                               (void *) &wifi_prov_handlers) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set provisioning endpoint");
        protocomm_ble_stop(g_prov->pc);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Provisioning started with BLE devname : '%s'", config.device_name);
    return ESP_OK;
}