#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; } ;
typedef  TYPE_5__ wifi_prov_config_set_data_t ;
struct TYPE_19__ {scalar_t__ (* set_config_handler ) (TYPE_5__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  ctx; } ;
typedef  TYPE_6__ wifi_prov_config_handlers_t ;
typedef  int /*<<< orphan*/  req_data ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_20__ {TYPE_8__* resp_set_config; int /*<<< orphan*/  payload_case; TYPE_4__* cmd_set_config; } ;
typedef  TYPE_7__ WiFiConfigPayload ;
struct TYPE_21__ {int /*<<< orphan*/  status; } ;
struct TYPE_16__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {int /*<<< orphan*/  channel; TYPE_3__ bssid; TYPE_2__ passphrase; TYPE_1__ ssid; } ;
typedef  TYPE_8__ RespSetConfig ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  STATUS__InternalError ; 
 int /*<<< orphan*/  STATUS__InvalidArgument ; 
 int /*<<< orphan*/  STATUS__Success ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WI_FI_CONFIG_PAYLOAD__PAYLOAD_RESP_SET_CONFIG ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resp_set_config__init (TYPE_8__*) ; 
 scalar_t__ stub1 (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t cmd_set_config_handler(WiFiConfigPayload *req,
                                        WiFiConfigPayload *resp, void  *priv_data)
{
    ESP_LOGD(TAG, "Enter cmd_set_config_handler");
    wifi_prov_config_handlers_t *h = (wifi_prov_config_handlers_t *) priv_data;
    if (!h) {
        ESP_LOGE(TAG, "Command invoked without handlers");
        return ESP_ERR_INVALID_STATE;
    }

    RespSetConfig *resp_payload = (RespSetConfig *) malloc(sizeof(RespSetConfig));
    if (resp_payload == NULL) {
        ESP_LOGE(TAG, "Error allocating memory");
        return ESP_ERR_NO_MEM;
    }
    resp_set_config__init(resp_payload);

    wifi_prov_config_set_data_t req_data;
    memset(&req_data, 0, sizeof(req_data));

    /* Check arguments provided in protobuf packet:
     * - SSID / Passphrase string length must be within the standard limits
     * - BSSID must either be NULL or have length equal to that imposed by the standard
     * If any of these conditions are not satisfied, don't invoke the handler and
     * send error status without closing connection */
    resp_payload->status = STATUS__InvalidArgument;
    if (req->cmd_set_config->bssid.len != 0 &&
        req->cmd_set_config->bssid.len != sizeof(req_data.bssid)) {
        ESP_LOGD(TAG, "Received invalid BSSID");
    } else if (req->cmd_set_config->ssid.len >= sizeof(req_data.ssid)) {
        ESP_LOGD(TAG, "Received invalid SSID");
    } else if (req->cmd_set_config->passphrase.len >= sizeof(req_data.password)) {
        ESP_LOGD(TAG, "Received invalid Passphrase");
    } else {
        /* The received SSID and Passphrase are not NULL terminated so
         * we memcpy over zeroed out arrays. Above length checks ensure
         * that there is atleast 1 extra byte for null termination */
        memcpy(req_data.ssid, req->cmd_set_config->ssid.data,
               req->cmd_set_config->ssid.len);
        memcpy(req_data.password, req->cmd_set_config->passphrase.data,
               req->cmd_set_config->passphrase.len);
        memcpy(req_data.bssid, req->cmd_set_config->bssid.data,
               req->cmd_set_config->bssid.len);
        req_data.channel = req->cmd_set_config->channel;
        if (h->set_config_handler(&req_data, &h->ctx) == ESP_OK) {
            resp_payload->status = STATUS__Success;
        } else {
            resp_payload->status = STATUS__InternalError;
        }
    }

    resp->payload_case = WI_FI_CONFIG_PAYLOAD__PAYLOAD_RESP_SET_CONFIG;
    resp->resp_set_config = resp_payload;
    return ESP_OK;
}