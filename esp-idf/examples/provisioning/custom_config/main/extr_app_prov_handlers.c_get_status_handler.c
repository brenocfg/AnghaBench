#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wifi_prov_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  auth_mode; int /*<<< orphan*/  channel; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ip_addr; } ;
struct TYPE_10__ {scalar_t__ wifi_state; int /*<<< orphan*/  fail_reason; TYPE_1__ conn_info; } ;
typedef  TYPE_2__ wifi_prov_config_get_data_t ;
struct TYPE_11__ {int /*<<< orphan*/  authmode; int /*<<< orphan*/  primary; scalar_t__ ssid; scalar_t__ bssid; } ;
typedef  TYPE_3__ wifi_ap_record_t ;
struct TYPE_12__ {int /*<<< orphan*/  ip; } ;
typedef  TYPE_4__ esp_netif_ip_info_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ WIFI_PROV_STA_CONNECTED ; 
 scalar_t__ WIFI_PROV_STA_DISCONNECTED ; 
 int /*<<< orphan*/  app_prov_get_wifi_disconnect_reason (int /*<<< orphan*/ *) ; 
 scalar_t__ app_prov_get_wifi_state (scalar_t__*) ; 
 int /*<<< orphan*/  esp_ip4addr_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_netif_get_handle_from_ifkey (char*) ; 
 int /*<<< orphan*/  esp_netif_get_ip_info (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  esp_wifi_sta_get_ap_info (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t get_status_handler(wifi_prov_config_get_data_t *resp_data, wifi_prov_ctx_t **ctx)
{
    /* Initialize to zero */
    memset(resp_data, 0, sizeof(wifi_prov_config_get_data_t));

    if (app_prov_get_wifi_state(&resp_data->wifi_state) != ESP_OK) {
        ESP_LOGW(TAG, "Prov app not running");
        return ESP_FAIL;
    }

    if (resp_data->wifi_state == WIFI_PROV_STA_CONNECTED) {
        ESP_LOGI(TAG, "Connected state");

        /* IP Addr assigned to STA */
        esp_netif_ip_info_t ip_info;
        esp_netif_get_ip_info(esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"), &ip_info);
        esp_ip4addr_ntoa(&ip_info.ip, resp_data->conn_info.ip_addr, sizeof(resp_data->conn_info.ip_addr));

        /* AP information to which STA is connected */
        wifi_ap_record_t ap_info;
        esp_wifi_sta_get_ap_info(&ap_info);
        memcpy(resp_data->conn_info.bssid, (char *)ap_info.bssid, sizeof(ap_info.bssid));
        memcpy(resp_data->conn_info.ssid,  (char *)ap_info.ssid,  sizeof(ap_info.ssid));
        resp_data->conn_info.channel   = ap_info.primary;
        resp_data->conn_info.auth_mode = ap_info.authmode;
    } else if (resp_data->wifi_state == WIFI_PROV_STA_DISCONNECTED) {
        ESP_LOGI(TAG, "Disconnected state");

        /* If disconnected, convey reason */
        app_prov_get_wifi_disconnect_reason(&resp_data->fail_reason);
    } else {
        ESP_LOGI(TAG, "Connecting state");
    }
    return ESP_OK;
}