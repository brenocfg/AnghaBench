#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int len; TYPE_4__* data; } ;
struct TYPE_22__ {struct TYPE_22__* sr1; int /*<<< orphan*/  payload_case; int /*<<< orphan*/  msg; TYPE_3__ device_verify_data; int /*<<< orphan*/  status; TYPE_2__* sc1; } ;
typedef  TYPE_4__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_23__ {scalar_t__ state; int /*<<< orphan*/  ctx_aes; TYPE_4__* client_pubkey; int /*<<< orphan*/  stb; int /*<<< orphan*/  rand; scalar_t__ nc_off; int /*<<< orphan*/  device_pubkey; int /*<<< orphan*/  sym_key; } ;
typedef  TYPE_5__ session_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  check_buf ;
struct TYPE_24__ {TYPE_4__* sec1; int /*<<< orphan*/  proto_case; } ;
struct TYPE_19__ {int len; TYPE_4__* data; } ;
struct TYPE_20__ {TYPE_1__ client_verify_data; } ;
typedef  TYPE_4__ SessionResp1 ;
typedef  TYPE_7__ SessionData ;
typedef  TYPE_4__ Sec1Payload ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int PUBLIC_KEY_LEN ; 
 int /*<<< orphan*/  SEC1_MSG_TYPE__Session_Response1 ; 
 int /*<<< orphan*/  SEC1_PAYLOAD__PAYLOAD_SR1 ; 
 int /*<<< orphan*/  SESSION_DATA__PROTO_SEC1 ; 
 scalar_t__ SESSION_STATE_CMD1 ; 
 scalar_t__ SESSION_STATE_DONE ; 
 int /*<<< orphan*/  STATUS__Success ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  hexdump (char*,TYPE_4__*,int) ; 
 scalar_t__ malloc (int) ; 
 int mbedtls_aes_crypt_ctr (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mbedtls_aes_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_aes_init (int /*<<< orphan*/ *) ; 
 int mbedtls_aes_setkey_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mbedtls_ssl_safer_memcmp (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec1_payload__init (TYPE_4__*) ; 
 int /*<<< orphan*/  session_resp1__init (TYPE_4__*) ; 

__attribute__((used)) static esp_err_t handle_session_command1(session_t *cur_session,
                                         uint32_t session_id,
                                         SessionData *req, SessionData *resp)
{
    ESP_LOGD(TAG, "Request to handle setup1_command");
    Sec1Payload *in = (Sec1Payload *) req->sec1;
    uint8_t check_buf[PUBLIC_KEY_LEN];
    int mbed_err;

    if (cur_session->state != SESSION_STATE_CMD1) {
        ESP_LOGE(TAG, "Invalid state of session %d (expected %d)", SESSION_STATE_CMD1, cur_session->state);
        return ESP_ERR_INVALID_STATE;
    }

    /* Initialize crypto context */
    mbedtls_aes_init(&cur_session->ctx_aes);
    memset(cur_session->stb, 0, sizeof(cur_session->stb));
    cur_session->nc_off = 0;

    hexdump("Client verifier", in->sc1->client_verify_data.data,
            in->sc1->client_verify_data.len);

    mbed_err = mbedtls_aes_setkey_enc(&cur_session->ctx_aes, cur_session->sym_key,
                                      sizeof(cur_session->sym_key)*8);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failure at mbedtls_aes_setkey_enc with error code : -0x%x", -mbed_err);
        mbedtls_aes_free(&cur_session->ctx_aes);
        return ESP_FAIL;
    }

    mbed_err = mbedtls_aes_crypt_ctr(&cur_session->ctx_aes,
                                     PUBLIC_KEY_LEN, &cur_session->nc_off,
                                     cur_session->rand, cur_session->stb,
                                     in->sc1->client_verify_data.data, check_buf);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failure at mbedtls_aes_crypt_ctr with error code : -0x%x", -mbed_err);
        mbedtls_aes_free(&cur_session->ctx_aes);
        return ESP_FAIL;
    }

    hexdump("Dec Client verifier", check_buf, sizeof(check_buf));

    /* constant time memcmp */
    if (mbedtls_ssl_safer_memcmp(check_buf, cur_session->device_pubkey,
                                 sizeof(cur_session->device_pubkey)) != 0) {
        ESP_LOGE(TAG, "Key mismatch. Close connection");
        mbedtls_aes_free(&cur_session->ctx_aes);
        return ESP_FAIL;
    }

    Sec1Payload *out = (Sec1Payload *) malloc(sizeof(Sec1Payload));
    SessionResp1 *out_resp = (SessionResp1 *) malloc(sizeof(SessionResp1));
    if (!out || !out_resp) {
        ESP_LOGE(TAG, "Error allocating memory for response1");
        free(out);
        free(out_resp);
        mbedtls_aes_free(&cur_session->ctx_aes);
        return ESP_ERR_NO_MEM;
    }

    sec1_payload__init(out);
    session_resp1__init(out_resp);
    out_resp->status = STATUS__Success;

    uint8_t *outbuf = (uint8_t *) malloc(PUBLIC_KEY_LEN);
    if (!outbuf) {
        ESP_LOGE(TAG, "Error allocating ciphertext buffer");
        free(out);
        free(out_resp);
        mbedtls_aes_free(&cur_session->ctx_aes);
        return ESP_ERR_NO_MEM;
    }

    mbed_err = mbedtls_aes_crypt_ctr(&cur_session->ctx_aes,
                                     PUBLIC_KEY_LEN, &cur_session->nc_off,
                                     cur_session->rand, cur_session->stb,
                                     cur_session->client_pubkey, outbuf);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failure at mbedtls_aes_crypt_ctr with error code : -0x%x", -mbed_err);
        free(outbuf);
        free(out);
        free(out_resp);
        mbedtls_aes_free(&cur_session->ctx_aes);
        return ESP_FAIL;
    }

    out_resp->device_verify_data.data = outbuf;
    out_resp->device_verify_data.len = PUBLIC_KEY_LEN;
    hexdump("Device verify data", outbuf, PUBLIC_KEY_LEN);

    out->msg = SEC1_MSG_TYPE__Session_Response1;
    out->payload_case = SEC1_PAYLOAD__PAYLOAD_SR1;
    out->sr1 = out_resp;

    resp->proto_case = SESSION_DATA__PROTO_SEC1;
    resp->sec1 = out;

    cur_session->state = SESSION_STATE_DONE;
    ESP_LOGD(TAG, "Secure session established successfully");
    return ESP_OK;
}