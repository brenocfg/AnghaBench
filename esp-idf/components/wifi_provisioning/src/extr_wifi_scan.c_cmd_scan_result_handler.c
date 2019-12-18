#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_22__ {int /*<<< orphan*/  bssid; int /*<<< orphan*/  auth; int /*<<< orphan*/  rssi; int /*<<< orphan*/  channel; int /*<<< orphan*/  ssid; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_6__ wifi_prov_scan_result_t ;
struct TYPE_23__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* scan_result ) (scalar_t__,TYPE_6__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_7__ wifi_prov_scan_handlers_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_21__ {int len; scalar_t__ data; } ;
struct TYPE_20__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct TYPE_24__ {TYPE_5__ bssid; int /*<<< orphan*/  auth; int /*<<< orphan*/  rssi; int /*<<< orphan*/  channel; TYPE_4__ ssid; } ;
typedef  TYPE_8__ WiFiScanResult ;
struct TYPE_25__ {int /*<<< orphan*/  status; TYPE_3__* cmd_scan_result; TYPE_10__* resp_scan_result; int /*<<< orphan*/  payload_case; } ;
typedef  TYPE_9__ WiFiScanPayload ;
struct TYPE_19__ {size_t count; scalar_t__ start_index; } ;
struct TYPE_16__ {size_t n_entries; TYPE_8__** entries; } ;
typedef  TYPE_10__ RespScanResult ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  STATUS__InternalError ; 
 int /*<<< orphan*/  STATUS__Success ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WI_FI_SCAN_PAYLOAD__PAYLOAD_RESP_SCAN_RESULT ; 
 scalar_t__ calloc (size_t,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resp_scan_result__init (TYPE_10__*) ; 
 scalar_t__ strndup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strnlen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wi_fi_scan_result__init (TYPE_8__*) ; 

__attribute__((used)) static esp_err_t cmd_scan_result_handler(WiFiScanPayload *req,
                                         WiFiScanPayload *resp, void *priv_data)
{
    esp_err_t err;
    wifi_prov_scan_result_t scan_result = {{0}, {0}, 0, 0, 0};
    WiFiScanResult **results = NULL;
    wifi_prov_scan_handlers_t *h = (wifi_prov_scan_handlers_t *) priv_data;
    if (!h) {
        ESP_LOGE(TAG, "Command invoked without handlers");
        return ESP_ERR_INVALID_STATE;
    }

    RespScanResult *resp_payload = (RespScanResult *) malloc(sizeof(RespScanResult));
    if (!resp_payload) {
        ESP_LOGE(TAG, "Error allocating memory");
        return ESP_ERR_NO_MEM;
    }
    resp_scan_result__init(resp_payload);

    resp->status = STATUS__Success;
    resp->payload_case = WI_FI_SCAN_PAYLOAD__PAYLOAD_RESP_SCAN_RESULT;
    resp->resp_scan_result = resp_payload;

    results = (WiFiScanResult **) calloc(req->cmd_scan_result->count,
                                         sizeof(WiFiScanResult *));
    if (!results) {
        ESP_LOGE(TAG, "Failed to allocate memory for results array");
        return ESP_ERR_NO_MEM;
    }
    resp_payload->entries = results;
    resp_payload->n_entries = req->cmd_scan_result->count;

    for (uint16_t i = 0; i < req->cmd_scan_result->count; i++) {
        err = h->scan_result(i + req->cmd_scan_result->start_index,
                             &scan_result, &h->ctx);
        if (err != ESP_OK) {
            resp->status = STATUS__InternalError;
            break;
        }

        results[i] = (WiFiScanResult *) malloc(sizeof(WiFiScanResult));
        if (!results[i]) {
            ESP_LOGE(TAG, "Failed to allocate memory for result entry");
            return ESP_ERR_NO_MEM;
        }
        wi_fi_scan_result__init(results[i]);

        results[i]->ssid.len = strnlen(scan_result.ssid, 32);
        results[i]->ssid.data = (uint8_t *) strndup(scan_result.ssid, 32);
        if (!results[i]->ssid.data) {
            ESP_LOGE(TAG, "Failed to allocate memory for scan result entry SSID");
            return ESP_ERR_NO_MEM;
        }

        results[i]->channel = scan_result.channel;
        results[i]->rssi = scan_result.rssi;
        results[i]->auth = scan_result.auth;

        results[i]->bssid.len = sizeof(scan_result.bssid);
        results[i]->bssid.data = malloc(results[i]->bssid.len);
        if (!results[i]->bssid.data) {
            ESP_LOGE(TAG, "Failed to allocate memory for scan result entry BSSID");
            return ESP_ERR_NO_MEM;
        }
        memcpy(results[i]->bssid.data, scan_result.bssid, results[i]->bssid.len);
    }
    return ESP_OK;
}