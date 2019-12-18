#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ id; scalar_t__ state; int /*<<< orphan*/  stb; int /*<<< orphan*/  rand; int /*<<< orphan*/  nc_off; int /*<<< orphan*/  ctx_aes; } ;
typedef  TYPE_1__ session_t ;
typedef  scalar_t__ protocomm_security_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ SESSION_STATE_DONE ; 
 int /*<<< orphan*/  TAG ; 
 int mbedtls_aes_crypt_ctr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t sec1_decrypt(protocomm_security_handle_t handle,
                              uint32_t session_id,
                              const uint8_t *inbuf, ssize_t inlen,
                              uint8_t *outbuf, ssize_t *outlen)
{
    session_t *cur_session = (session_t *) handle;
    if (!cur_session) {
        return ESP_ERR_INVALID_ARG;
    }

    if (*outlen < inlen) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!cur_session || cur_session->id != session_id) {
        ESP_LOGE(TAG, "Session with ID %d not found", session_id);
        return ESP_ERR_INVALID_STATE;
    }

    if (cur_session->state != SESSION_STATE_DONE) {
        ESP_LOGE(TAG, "Secure session not established");
        return ESP_ERR_INVALID_STATE;
    }

    *outlen = inlen;
    int ret = mbedtls_aes_crypt_ctr(&cur_session->ctx_aes, inlen, &cur_session->nc_off,
                                    cur_session->rand, cur_session->stb, inbuf, outbuf);
    if (ret != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_aes_crypt_ctr with error code : %d", ret);
        return ESP_FAIL;
    }
    return ESP_OK;
}