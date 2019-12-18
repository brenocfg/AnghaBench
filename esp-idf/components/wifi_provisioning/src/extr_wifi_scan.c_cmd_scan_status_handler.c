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
struct TYPE_7__ {scalar_t__ (* scan_status ) (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ wifi_prov_scan_handlers_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_8__ {TYPE_3__* resp_scan_status; int /*<<< orphan*/  payload_case; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ WiFiScanPayload ;
struct TYPE_9__ {int scan_finished; int /*<<< orphan*/  result_count; } ;
typedef  TYPE_3__ RespScanStatus ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  STATUS__InternalError ; 
 int /*<<< orphan*/  STATUS__Success ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WI_FI_SCAN_PAYLOAD__PAYLOAD_RESP_SCAN_STATUS ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  resp_scan_status__init (TYPE_3__*) ; 
 scalar_t__ stub1 (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t cmd_scan_status_handler(WiFiScanPayload *req,
                                         WiFiScanPayload *resp, void *priv_data)
{
    bool scan_finished = false;
    uint16_t result_count = 0;

    wifi_prov_scan_handlers_t *h = (wifi_prov_scan_handlers_t *) priv_data;
    if (!h) {
        ESP_LOGE(TAG, "Command invoked without handlers");
        return ESP_ERR_INVALID_STATE;
    }

    RespScanStatus *resp_payload = (RespScanStatus *) malloc(sizeof(RespScanStatus));
    if (!resp_payload) {
        ESP_LOGE(TAG, "Error allocating memory");
        return ESP_ERR_NO_MEM;
    }

    resp_scan_status__init(resp_payload);
    resp->status = (h->scan_status(&scan_finished, &result_count, &h->ctx) == ESP_OK ?
                            STATUS__Success : STATUS__InternalError);
    resp_payload->scan_finished = scan_finished;
    resp_payload->result_count = result_count;
    resp->payload_case = WI_FI_SCAN_PAYLOAD__PAYLOAD_RESP_SCAN_STATUS;
    resp->resp_scan_status = resp_payload;
    return ESP_OK;
}