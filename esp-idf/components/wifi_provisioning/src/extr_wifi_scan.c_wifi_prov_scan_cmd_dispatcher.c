#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ esp_err_t ;
struct TYPE_7__ {int /*<<< orphan*/  msg; } ;
typedef  TYPE_1__ WiFiScanPayload ;
struct TYPE_8__ {scalar_t__ (* command_handler ) (TYPE_1__*,TYPE_1__*,void*) ;} ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_6__* cmd_table ; 
 int lookup_cmd_handler (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,TYPE_1__*,void*) ; 

__attribute__((used)) static esp_err_t wifi_prov_scan_cmd_dispatcher(WiFiScanPayload *req,
                                               WiFiScanPayload *resp, void *priv_data)
{
    esp_err_t ret;

    ESP_LOGD(TAG, "In wifi_prov_scan_cmd_dispatcher Cmd=%d", req->msg);

    int cmd_index = lookup_cmd_handler(req->msg);
    if (cmd_index < 0) {
        ESP_LOGE(TAG, "Invalid command handler lookup");
        return ESP_FAIL;
    }

    ret = cmd_table[cmd_index].command_handler(req, resp, priv_data);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error executing command handler");
        return ESP_FAIL;
    }

    return ESP_OK;
}