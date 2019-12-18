#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ esp_err_t ;
typedef  scalar_t__ (* custom_prov_config_handler_t ) (TYPE_1__*) ;
struct TYPE_10__ {int /*<<< orphan*/  version; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ custom_config_t ;
struct TYPE_12__ {int /*<<< orphan*/  version; int /*<<< orphan*/  info; } ;
struct TYPE_11__ {int dummy; void* status; } ;
typedef  TYPE_3__ CustomConfigResponse ;
typedef  TYPE_4__ CustomConfigRequest ;

/* Variables and functions */
 void* CUSTOM_CONFIG_STATUS__ConfigFail ; 
 void* CUSTOM_CONFIG_STATUS__ConfigSuccess ; 
 int ESP_ERR_INVALID_ARG ; 
 int ESP_ERR_NO_MEM ; 
 int ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  custom_config_request__free_unpacked (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* custom_config_request__unpack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  custom_config_response__get_packed_size (TYPE_3__*) ; 
 int /*<<< orphan*/  custom_config_response__init (TYPE_3__*) ; 
 int /*<<< orphan*/  custom_config_response__pack (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int custom_prov_config_data_handler(uint32_t session_id, const uint8_t *inbuf, ssize_t inlen, uint8_t **outbuf, ssize_t *outlen, void *priv_data)
{
    CustomConfigRequest *req;
    CustomConfigResponse resp;
    custom_prov_config_handler_t app_handler_custom_config = (custom_prov_config_handler_t) priv_data;

    req = custom_config_request__unpack(NULL, inlen, inbuf);
    if (!req) {
        ESP_LOGE(TAG, "Unable to unpack config data");
        return ESP_ERR_INVALID_ARG;
    }

    custom_config_response__init(&resp);
    resp.status = CUSTOM_CONFIG_STATUS__ConfigFail;

    if (app_handler_custom_config) {
        custom_config_t config;
        strlcpy(config.info, req->info, sizeof(config.info));
        config.version = req->version;

        esp_err_t err = app_handler_custom_config(&config);
        resp.status = (err == ESP_OK) ? CUSTOM_CONFIG_STATUS__ConfigSuccess :
                                        CUSTOM_CONFIG_STATUS__ConfigFail;
    }
    custom_config_request__free_unpacked(req, NULL);

    resp.dummy = 47;    // Set a non zero value of dummy

    *outlen = custom_config_response__get_packed_size(&resp);
    if (*outlen <= 0) {
        ESP_LOGE(TAG, "Invalid encoding for response");
        return ESP_FAIL;
    }

    *outbuf = (uint8_t *) malloc(*outlen);
    if (*outbuf == NULL) {
        ESP_LOGE(TAG, "System out of memory");
        return ESP_ERR_NO_MEM;
    }

    custom_config_response__pack(&resp, *outbuf);
    return ESP_OK;
}