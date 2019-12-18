#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_10__ {scalar_t__ msg; } ;
typedef  TYPE_1__ WiFiConfigPayload ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wi_fi_config_payload__free_unpacked (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wi_fi_config_payload__get_packed_size (TYPE_1__*) ; 
 int /*<<< orphan*/  wi_fi_config_payload__init (TYPE_1__*) ; 
 int /*<<< orphan*/  wi_fi_config_payload__pack (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* wi_fi_config_payload__unpack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wifi_prov_config_command_cleanup (TYPE_1__*,void*) ; 
 scalar_t__ wifi_prov_config_command_dispatcher (TYPE_1__*,TYPE_1__*,void*) ; 

esp_err_t wifi_prov_config_data_handler(uint32_t session_id, const uint8_t *inbuf, ssize_t inlen,
                                        uint8_t **outbuf, ssize_t *outlen, void *priv_data)
{
    WiFiConfigPayload *req;
    WiFiConfigPayload resp;
    esp_err_t ret;

    req = wi_fi_config_payload__unpack(NULL, inlen, inbuf);
    if (!req) {
        ESP_LOGE(TAG, "Unable to unpack config data");
        return ESP_ERR_INVALID_ARG;
    }

    wi_fi_config_payload__init(&resp);
    ret = wifi_prov_config_command_dispatcher(req, &resp, priv_data);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Proto command dispatcher error %d", ret);
        return ESP_FAIL;
    }

    resp.msg = req->msg + 1; /* Response is request + 1 */
    wi_fi_config_payload__free_unpacked(req, NULL);

    *outlen = wi_fi_config_payload__get_packed_size(&resp);
    if (*outlen <= 0) {
        ESP_LOGE(TAG, "Invalid encoding for response");
        return ESP_FAIL;
    }

    *outbuf = (uint8_t *) malloc(*outlen);
    if (!*outbuf) {
        ESP_LOGE(TAG, "System out of memory");
        return ESP_ERR_NO_MEM;
    }
    wi_fi_config_payload__pack(&resp, *outbuf);
    wifi_prov_config_command_cleanup(&resp, priv_data);

    return ESP_OK;
}