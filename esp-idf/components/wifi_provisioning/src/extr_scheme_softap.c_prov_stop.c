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
typedef  int /*<<< orphan*/  protocomm_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  mdns_service_remove (char*,char*) ; 
 scalar_t__ protocomm_httpd_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t prov_stop(protocomm_t *pc)
{
    esp_err_t err = protocomm_httpd_stop(pc);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Error occurred while stopping protocomm_httpd");
    }

    mdns_service_remove("_esp_wifi_prov", "_tcp");
    return err;
}