#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ctx; int /*<<< orphan*/  scan_result; int /*<<< orphan*/  scan_status; int /*<<< orphan*/  scan_start; } ;
typedef  TYPE_1__ wifi_prov_scan_handlers_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  scan_result ; 
 int /*<<< orphan*/  scan_start ; 
 int /*<<< orphan*/  scan_status ; 

esp_err_t get_wifi_scan_handlers(wifi_prov_scan_handlers_t *ptr)
{
    if (!ptr) {
        return ESP_ERR_INVALID_ARG;
    }
    ptr->scan_start  = scan_start;
    ptr->scan_status = scan_status;
    ptr->scan_result = scan_result;
    ptr->ctx = NULL;
    return ESP_OK;
}