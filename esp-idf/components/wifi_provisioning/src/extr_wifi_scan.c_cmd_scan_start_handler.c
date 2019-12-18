#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ (* scan_start ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ wifi_prov_scan_handlers_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_8__ {int /*<<< orphan*/ * resp_scan_start; int /*<<< orphan*/  payload_case; TYPE_1__* cmd_scan_start; int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ WiFiScanPayload ;
struct TYPE_6__ {int /*<<< orphan*/  period_ms; int /*<<< orphan*/  group_channels; int /*<<< orphan*/  passive; int /*<<< orphan*/  blocking; } ;
typedef  int /*<<< orphan*/  RespScanStart ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  STATUS__InternalError ; 
 int /*<<< orphan*/  STATUS__Success ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WI_FI_SCAN_PAYLOAD__PAYLOAD_RESP_SCAN_START ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  resp_scan_start__init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t cmd_scan_start_handler(WiFiScanPayload *req,
                                        WiFiScanPayload *resp, void *priv_data)
{
    wifi_prov_scan_handlers_t *h = (wifi_prov_scan_handlers_t *) priv_data;
    if (!h) {
        ESP_LOGE(TAG, "Command invoked without handlers");
        return ESP_ERR_INVALID_STATE;
    }

    RespScanStart *resp_payload = (RespScanStart *) malloc(sizeof(RespScanStart));
    if (!resp_payload) {
        ESP_LOGE(TAG, "Error allocating memory");
        return ESP_ERR_NO_MEM;
    }

    resp_scan_start__init(resp_payload);
    resp->status = (h->scan_start(req->cmd_scan_start->blocking,
                                  req->cmd_scan_start->passive,
                                  req->cmd_scan_start->group_channels,
                                  req->cmd_scan_start->period_ms,
                                  &h->ctx) == ESP_OK ?
                            STATUS__Success : STATUS__InternalError);
    resp->payload_case = WI_FI_SCAN_PAYLOAD__PAYLOAD_RESP_SCAN_START;
    resp->resp_scan_start = resp_payload;
    return ESP_OK;
}