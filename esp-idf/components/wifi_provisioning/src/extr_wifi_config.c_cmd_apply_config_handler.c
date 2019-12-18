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
struct TYPE_7__ {scalar_t__ (* apply_config_handler ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ wifi_prov_config_handlers_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_8__ {TYPE_3__* resp_apply_config; int /*<<< orphan*/  payload_case; } ;
typedef  TYPE_2__ WiFiConfigPayload ;
struct TYPE_9__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ RespApplyConfig ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  STATUS__InternalError ; 
 int /*<<< orphan*/  STATUS__Success ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WI_FI_CONFIG_PAYLOAD__PAYLOAD_RESP_APPLY_CONFIG ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  resp_apply_config__init (TYPE_3__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t cmd_apply_config_handler(WiFiConfigPayload *req,
                                          WiFiConfigPayload *resp, void  *priv_data)
{
    ESP_LOGD(TAG, "Enter cmd_apply_config_handler");
    wifi_prov_config_handlers_t *h = (wifi_prov_config_handlers_t *) priv_data;
    if (!h) {
        ESP_LOGE(TAG, "Command invoked without handlers");
        return ESP_ERR_INVALID_STATE;
    }

    RespApplyConfig *resp_payload = (RespApplyConfig *) malloc(sizeof(RespApplyConfig));
    if (!resp_payload) {
        ESP_LOGE(TAG, "Error allocating memory");
        return ESP_ERR_NO_MEM;
    }

    resp_apply_config__init(resp_payload);

    if (h->apply_config_handler(&h->ctx) == ESP_OK) {
        resp_payload->status = STATUS__Success;
    } else {
        resp_payload->status = STATUS__InternalError;
    }

    resp->payload_case = WI_FI_CONFIG_PAYLOAD__PAYLOAD_RESP_APPLY_CONFIG;
    resp->resp_apply_config = resp_payload;
    return ESP_OK;
}