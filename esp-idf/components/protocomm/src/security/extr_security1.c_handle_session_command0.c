#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_22__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_18__ ;
typedef  struct TYPE_36__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_43__ {scalar_t__ state; int /*<<< orphan*/ * rand; int /*<<< orphan*/ * sym_key; int /*<<< orphan*/ * client_pubkey; int /*<<< orphan*/ * device_pubkey; } ;
typedef  TYPE_5__ session_t ;
struct TYPE_44__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_6__ protocomm_security_pop_t ;
struct TYPE_40__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_38__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_39__ {int /*<<< orphan*/  X; int /*<<< orphan*/  Z; } ;
struct TYPE_37__ {int /*<<< orphan*/  X; } ;
struct TYPE_45__ {struct TYPE_45__* sr0; int /*<<< orphan*/  payload_case; int /*<<< orphan*/  msg; TYPE_2__ device_random; TYPE_1__ device_pubkey; int /*<<< orphan*/  status; int /*<<< orphan*/  z; int /*<<< orphan*/  d; TYPE_22__ Qp; int /*<<< orphan*/  grp; TYPE_4__* sc0; TYPE_18__ Q; } ;
typedef  TYPE_7__ mbedtls_entropy_context ;
typedef  TYPE_7__ mbedtls_ecdh_context ;
typedef  TYPE_7__ mbedtls_ctr_drbg_context ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_41__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_42__ {TYPE_3__ client_pubkey; } ;
struct TYPE_36__ {TYPE_7__* sec1; int /*<<< orphan*/  proto_case; } ;
typedef  TYPE_7__ SessionResp0 ;
typedef  TYPE_11__ SessionData ;
typedef  TYPE_7__ Sec1Payload ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MBEDTLS_ECP_DP_CURVE25519 ; 
 int PUBLIC_KEY_LEN ; 
 int /*<<< orphan*/  SEC1_MSG_TYPE__Session_Response0 ; 
 int /*<<< orphan*/  SEC1_PAYLOAD__PAYLOAD_SR0 ; 
 int /*<<< orphan*/  SESSION_DATA__PROTO_SEC1 ; 
 scalar_t__ SESSION_STATE_CMD0 ; 
 scalar_t__ SESSION_STATE_CMD1 ; 
 int /*<<< orphan*/  STATUS__Success ; 
 int SZ_RANDOM ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  flip_endian (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 
 int /*<<< orphan*/  hexdump (char*,int /*<<< orphan*/ *,int) ; 
 TYPE_7__* malloc (int) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_free (TYPE_7__*) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_init (TYPE_7__*) ; 
 int mbedtls_ctr_drbg_random (TYPE_7__*,int /*<<< orphan*/ *,int) ; 
 int mbedtls_ctr_drbg_seed (TYPE_7__*,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mbedtls_ecdh_compute_shared (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_22__*,int /*<<< orphan*/ *,int (*) (TYPE_7__*,int /*<<< orphan*/ *,int),TYPE_7__*) ; 
 int /*<<< orphan*/  mbedtls_ecdh_free (TYPE_7__*) ; 
 int mbedtls_ecdh_gen_public (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_18__*,int (*) (TYPE_7__*,int /*<<< orphan*/ *,int),TYPE_7__*) ; 
 int /*<<< orphan*/  mbedtls_ecdh_init (TYPE_7__*) ; 
 int mbedtls_ecp_group_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_entropy_free (TYPE_7__*) ; 
 int /*<<< orphan*/  mbedtls_entropy_func ; 
 int /*<<< orphan*/  mbedtls_entropy_init (TYPE_7__*) ; 
 int mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 
 int mbedtls_mpi_read_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mbedtls_mpi_write_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mbedtls_sha256_ret (unsigned char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec1_payload__init (TYPE_7__*) ; 
 int /*<<< orphan*/  session_resp0__init (TYPE_7__*) ; 

__attribute__((used)) static esp_err_t handle_session_command0(session_t *cur_session,
                                         uint32_t session_id,
                                         SessionData *req, SessionData *resp,
                                         const protocomm_security_pop_t *pop)
{
    ESP_LOGD(TAG, "Request to handle setup0_command");
    Sec1Payload *in = (Sec1Payload *) req->sec1;
    esp_err_t ret;
    int mbed_err;

    if (cur_session->state != SESSION_STATE_CMD0) {
        ESP_LOGE(TAG, "Invalid state of session %d (expected %d)", SESSION_STATE_CMD0, cur_session->state);
        return ESP_ERR_INVALID_STATE;
    }

    if (in->sc0->client_pubkey.len != PUBLIC_KEY_LEN) {
        ESP_LOGE(TAG, "Invalid public key length");
        return ESP_ERR_INVALID_ARG;
    }

    mbedtls_ecdh_context     *ctx_server = malloc(sizeof(mbedtls_ecdh_context));
    mbedtls_entropy_context  *entropy    = malloc(sizeof(mbedtls_entropy_context));
    mbedtls_ctr_drbg_context *ctr_drbg   = malloc(sizeof(mbedtls_ctr_drbg_context));
    if (!ctx_server || !entropy || !ctr_drbg) {
        ESP_LOGE(TAG, "Failed to allocate memory for mbedtls context");
        free(ctx_server);
        free(entropy);
        free(ctr_drbg);
        return ESP_ERR_NO_MEM;
    }

    mbedtls_ecdh_init(ctx_server);
    mbedtls_ctr_drbg_init(ctr_drbg);
    mbedtls_entropy_init(entropy);

    mbed_err = mbedtls_ctr_drbg_seed(ctr_drbg, mbedtls_entropy_func,
                                     entropy, NULL, 0);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_ctr_drbg_seed with error code : -0x%x", -mbed_err);
        ret = ESP_FAIL;
        goto exit_cmd0;
    }

    mbed_err = mbedtls_ecp_group_load(&ctx_server->grp, MBEDTLS_ECP_DP_CURVE25519);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_ecp_group_load with error code : -0x%x", -mbed_err);
        ret = ESP_FAIL;
        goto exit_cmd0;
    }

    mbed_err = mbedtls_ecdh_gen_public(&ctx_server->grp, &ctx_server->d, &ctx_server->Q,
                                       mbedtls_ctr_drbg_random, ctr_drbg);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_ecdh_gen_public with error code : -0x%x", -mbed_err);
        ret = ESP_FAIL;
        goto exit_cmd0;
    }

    mbed_err = mbedtls_mpi_write_binary(&ctx_server->Q.X,
                                        cur_session->device_pubkey,
                                        PUBLIC_KEY_LEN);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_mpi_write_binary with error code : -0x%x", -mbed_err);
        ret = ESP_FAIL;
        goto exit_cmd0;
    }
    flip_endian(cur_session->device_pubkey, PUBLIC_KEY_LEN);

    memcpy(cur_session->client_pubkey, in->sc0->client_pubkey.data, PUBLIC_KEY_LEN);

    uint8_t *dev_pubkey = cur_session->device_pubkey;
    uint8_t *cli_pubkey = cur_session->client_pubkey;
    hexdump("Device pubkey", dev_pubkey, PUBLIC_KEY_LEN);
    hexdump("Client pubkey", cli_pubkey, PUBLIC_KEY_LEN);

    mbed_err = mbedtls_mpi_lset(&ctx_server->Qp.Z, 1);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_mpi_lset with error code : -0x%x", -mbed_err);
        ret = ESP_FAIL;
        goto exit_cmd0;
    }

    flip_endian(cur_session->client_pubkey, PUBLIC_KEY_LEN);
    mbed_err = mbedtls_mpi_read_binary(&ctx_server->Qp.X, cli_pubkey, PUBLIC_KEY_LEN);
    flip_endian(cur_session->client_pubkey, PUBLIC_KEY_LEN);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_mpi_read_binary with error code : -0x%x", -mbed_err);
        ret = ESP_FAIL;
        goto exit_cmd0;
    }

    mbed_err = mbedtls_ecdh_compute_shared(&ctx_server->grp, &ctx_server->z, &ctx_server->Qp,
                                           &ctx_server->d, mbedtls_ctr_drbg_random, ctr_drbg);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_ecdh_compute_shared with error code : -0x%x", -mbed_err);
        ret = ESP_FAIL;
        goto exit_cmd0;
    }

    mbed_err = mbedtls_mpi_write_binary(&ctx_server->z, cur_session->sym_key, PUBLIC_KEY_LEN);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_mpi_write_binary with error code : -0x%x", -mbed_err);
        ret = ESP_FAIL;
        goto exit_cmd0;
    }
    flip_endian(cur_session->sym_key, PUBLIC_KEY_LEN);

    if (pop != NULL && pop->data != NULL && pop->len != 0) {
        ESP_LOGD(TAG, "Adding proof of possession");
        uint8_t sha_out[PUBLIC_KEY_LEN];

        mbed_err = mbedtls_sha256_ret((const unsigned char *) pop->data, pop->len, sha_out, 0);
        if (mbed_err != 0) {
            ESP_LOGE(TAG, "Failed at mbedtls_sha256_ret with error code : -0x%x", -mbed_err);
            ret = ESP_FAIL;
            goto exit_cmd0;
        }

        for (int i = 0; i < PUBLIC_KEY_LEN; i++) {
            cur_session->sym_key[i] ^= sha_out[i];
        }
    }

    hexdump("Shared key", cur_session->sym_key, PUBLIC_KEY_LEN);

    mbed_err = mbedtls_ctr_drbg_random(ctr_drbg, cur_session->rand, SZ_RANDOM);
    if (mbed_err != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_ctr_drbg_random with error code : -0x%x", -mbed_err);
        ret = ESP_FAIL;
        goto exit_cmd0;
    }

    hexdump("Device random", cur_session->rand, SZ_RANDOM);

    Sec1Payload *out = (Sec1Payload *) malloc(sizeof(Sec1Payload));
    SessionResp0 *out_resp = (SessionResp0 *) malloc(sizeof(SessionResp0));
    if (!out || !out_resp) {
        ESP_LOGE(TAG, "Error allocating memory for response0");
        ret = ESP_ERR_NO_MEM;
        free(out);
        free(out_resp);
        goto exit_cmd0;
    }

    sec1_payload__init(out);
    session_resp0__init(out_resp);

    out_resp->status = STATUS__Success;

    out_resp->device_pubkey.data = dev_pubkey;
    out_resp->device_pubkey.len = PUBLIC_KEY_LEN;

    out_resp->device_random.data = (uint8_t *) cur_session->rand;
    out_resp->device_random.len = SZ_RANDOM;

    out->msg = SEC1_MSG_TYPE__Session_Response0;
    out->payload_case = SEC1_PAYLOAD__PAYLOAD_SR0;
    out->sr0 = out_resp;

    resp->proto_case = SESSION_DATA__PROTO_SEC1;
    resp->sec1 = out;

    cur_session->state = SESSION_STATE_CMD1;

    ESP_LOGD(TAG, "Session setup phase1 done");
    ret = ESP_OK;

exit_cmd0:
    mbedtls_ecdh_free(ctx_server);
    free(ctx_server);

    mbedtls_ctr_drbg_free(ctr_drbg);
    free(ctr_drbg);

    mbedtls_entropy_free(entropy);
    free(entropy);

    return ret;
}