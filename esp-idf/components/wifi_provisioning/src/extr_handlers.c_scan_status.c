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
typedef  int /*<<< orphan*/  wifi_prov_scan_ctx_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int wifi_prov_mgr_wifi_scan_finished () ; 
 int /*<<< orphan*/  wifi_prov_mgr_wifi_scan_result_count () ; 

__attribute__((used)) static esp_err_t scan_status(bool *scan_finished,
                             uint16_t *result_count,
                             wifi_prov_scan_ctx_t **ctx)
{
    *scan_finished = wifi_prov_mgr_wifi_scan_finished();
    *result_count  = wifi_prov_mgr_wifi_scan_result_count();
    return ESP_OK;
}