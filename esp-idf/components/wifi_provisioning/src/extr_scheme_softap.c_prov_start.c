#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
struct TYPE_7__ {TYPE_1__ config; } ;
struct TYPE_9__ {TYPE_2__ data; } ;
struct TYPE_8__ {TYPE_4__ httpd_config; int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; } ;
typedef  TYPE_3__ wifi_prov_softap_config_t ;
typedef  int /*<<< orphan*/  protocomm_t ;
typedef  TYPE_4__ protocomm_httpd_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  mdns_service_add (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdns_service_txt_item_set (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  protocomm_httpd_start (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  protocomm_httpd_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_wifi_ap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t prov_start(protocomm_t *pc, void *config)
{
    if (!pc) {
        ESP_LOGE(TAG, "Protocomm handle cannot be null");
        return ESP_ERR_INVALID_ARG;
    }

    if (!config) {
        ESP_LOGE(TAG, "Cannot start with null configuration");
        return ESP_ERR_INVALID_ARG;
    }

    wifi_prov_softap_config_t *softap_config = (wifi_prov_softap_config_t *) config;

    protocomm_httpd_config_t *httpd_config = &softap_config->httpd_config;

    /* Start protocomm server on top of HTTP */
    esp_err_t err = protocomm_httpd_start(pc, httpd_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start protocomm HTTP server");
        return err;
    }

    /* Start Wi-Fi softAP with specified ssid and password */
    err = start_wifi_ap(softap_config->ssid, softap_config->password);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start Wi-Fi AP");
        protocomm_httpd_stop(pc);
        return err;
    }

    /* Add mDNS service for allowing discovery of provisioning
     * service on the SoftAP network (Optional). Even though
     * this is an http service we identify it by _esp_wifi_prov so
     * that application is free to use _http without conflict */
    err = mdns_service_add("Wi-Fi Provisioning Service", "_esp_wifi_prov", "_tcp",
                           softap_config->httpd_config.data.config.port, NULL, 0);
    if (err != ESP_OK) {
        /* mDNS is not mandatory for provisioning to work,
         * so print warning and return without failure */
        ESP_LOGW(TAG, "Error adding mDNS service! Check if mDNS is running");
    } else {
        /* Information to identify the roles of the various
         * protocomm endpoint URIs provided by the service */
        err |= mdns_service_txt_item_set("_esp_wifi_prov", "_tcp", "version_endpoint", "/proto-ver");
        err |= mdns_service_txt_item_set("_esp_wifi_prov", "_tcp", "session_endpoint", "/prov-session");
        err |= mdns_service_txt_item_set("_esp_wifi_prov", "_tcp", "config_endpoint", "/prov-config");
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Error adding mDNS service text item");
        }
    }
    return ESP_OK;
}