#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  protocomm_security_pop_t ;
typedef  int /*<<< orphan*/  protocomm_security_handle_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_12__ {scalar_t__ sec_ver; } ;
struct TYPE_11__ {scalar_t__ ver; } ;
typedef  TYPE_1__ SessionData ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 TYPE_10__ protocomm_security0 ; 
 scalar_t__ sec0_session_setup (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sec0_session_setup_cleanup (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  session_data__free_unpacked (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_data__get_packed_size (TYPE_1__*) ; 
 int /*<<< orphan*/  session_data__init (TYPE_1__*) ; 
 int /*<<< orphan*/  session_data__pack (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* session_data__unpack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static esp_err_t sec0_req_handler(protocomm_security_handle_t handle,
                                  const protocomm_security_pop_t *pop,
                                  uint32_t session_id,
                                  const uint8_t *inbuf, ssize_t inlen,
                                  uint8_t **outbuf, ssize_t *outlen,
                                  void *priv_data)
{
    SessionData *req;
    SessionData resp;
    esp_err_t ret;

    req = session_data__unpack(NULL, inlen, inbuf);
    if (!req) {
        ESP_LOGE(TAG, "Unable to unpack setup_req");
        return ESP_ERR_INVALID_ARG;
    }
    if (req->sec_ver != protocomm_security0.ver) {
        ESP_LOGE(TAG, "Security version mismatch. Closing connection");
        session_data__free_unpacked(req, NULL);
        return ESP_ERR_INVALID_ARG;
    }

    session_data__init(&resp);
    ret = sec0_session_setup(session_id, req, &resp, pop);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Session setup error %d", ret);
        session_data__free_unpacked(req, NULL);
        return ESP_FAIL;
    }

    resp.sec_ver = req->sec_ver;
    session_data__free_unpacked(req, NULL);

    *outlen = session_data__get_packed_size(&resp);
    *outbuf = (uint8_t *) malloc(*outlen);
    if (!*outbuf) {
        ESP_LOGE(TAG, "System out of memory");
        return ESP_ERR_NO_MEM;
    }
    session_data__pack(&resp, *outbuf);

    sec0_session_setup_cleanup(session_id, &resp);
    return ESP_OK;
}