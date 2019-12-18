#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wifi_prov_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; } ;
typedef  TYPE_2__ wifi_prov_config_set_data_t ;
struct TYPE_7__ {scalar_t__ password; scalar_t__ ssid; } ;
struct TYPE_9__ {TYPE_1__ sta; } ;
typedef  TYPE_3__ wifi_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free_config (int /*<<< orphan*/ **) ; 
 TYPE_3__* get_config (int /*<<< orphan*/ **) ; 
 TYPE_3__* new_config (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t set_config_handler(const wifi_prov_config_set_data_t *req_data, wifi_prov_ctx_t **ctx)
{
    wifi_config_t *wifi_cfg = get_config(ctx);
    if (wifi_cfg) {
        free_config(ctx);
    }

    wifi_cfg = new_config(ctx);
    if (!wifi_cfg) {
        ESP_LOGE(TAG, "Unable to alloc wifi config");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "WiFi Credentials Received : \n\tssid %s \n\tpassword %s",
             req_data->ssid, req_data->password);

    /* Using strncpy allows the max SSID length to be 32 bytes (as per 802.11 standard).
     * But this doesn't guarantee that the saved SSID will be null terminated, because
     * wifi_cfg->sta.ssid is also 32 bytes long (without extra 1 byte for null character).
     * Although, this is not a matter for concern because esp_wifi library reads the SSID
     * upto 32 bytes in absence of null termination */
    strncpy((char *) wifi_cfg->sta.ssid, req_data->ssid, sizeof(wifi_cfg->sta.ssid));
    strlcpy((char *) wifi_cfg->sta.password, req_data->password, sizeof(wifi_cfg->sta.password));
    return ESP_OK;
}