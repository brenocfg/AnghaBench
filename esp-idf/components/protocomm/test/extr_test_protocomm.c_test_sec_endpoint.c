#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_12__ {int /*<<< orphan*/  X; } ;
struct TYPE_11__ {TYPE_8__ Q; int /*<<< orphan*/  d; int /*<<< orphan*/  grp; } ;
struct TYPE_10__ {scalar_t__ sec_ver; int /*<<< orphan*/  entropy; int /*<<< orphan*/  ctr_drbg; TYPE_7__ ctx_client; int /*<<< orphan*/  client_pubkey; scalar_t__ weak; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ session_t ;
typedef  int esp_err_t ;
typedef  int /*<<< orphan*/  SessionData ;

/* Variables and functions */
 int ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  MBEDTLS_ECP_DP_CURVE25519 ; 
 int /*<<< orphan*/  PUBLIC_KEY_LEN ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  cleanup_command0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_command1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flip_endian (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_random ; 
 int mbedtls_ctr_drbg_seed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ecdh_free (TYPE_7__*) ; 
 int mbedtls_ecdh_gen_public (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecdh_init (TYPE_7__*) ; 
 int mbedtls_ecp_group_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_entropy_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_entropy_func ; 
 int /*<<< orphan*/  mbedtls_entropy_init (int /*<<< orphan*/ *) ; 
 int mbedtls_mpi_read_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_mpi_write_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int prepare_command0 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int prepare_command1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int protocomm_req_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  session_data__free_unpacked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ session_data__get_packed_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_data__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_data__pack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * session_data__unpack (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_pc ; 
 int verify_response0 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int verify_response1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t test_sec_endpoint(session_t *session)
{
    if (session->sec_ver == 0) {
        return ESP_OK;
    }

    uint32_t session_id = session->id;

    int ret = ESP_FAIL;
    SessionData req;
    SessionData *resp;
    ssize_t  inlen = 0;
    uint8_t *inbuf = NULL;
    ssize_t  outlen = 0;
    uint8_t *outbuf = NULL;

    mbedtls_ecdh_init(&session->ctx_client);
    mbedtls_ctr_drbg_init(&session->ctr_drbg);

    mbedtls_entropy_init(&session->entropy);
    ret = mbedtls_ctr_drbg_seed(&session->ctr_drbg, mbedtls_entropy_func,
                                &session->entropy, NULL, 0);
    if (ret != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_ctr_drbg_seed with error code : %d", ret);
        goto abort_test_sec_endpoint;
    }

    ret = mbedtls_ecp_group_load(&session->ctx_client.grp, MBEDTLS_ECP_DP_CURVE25519);
    if (ret != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_ecp_group_load with error code : %d", ret);
        goto abort_test_sec_endpoint;
    }

    ret = mbedtls_ecdh_gen_public(&session->ctx_client.grp,
                                  &session->ctx_client.d,
                                  &session->ctx_client.Q,
                                  mbedtls_ctr_drbg_random,
                                  &session->ctr_drbg);
    if (ret != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_ecdh_gen_public with error code : %d", ret);
        goto abort_test_sec_endpoint;
    }

    if (session->weak) {
        /* Read zero client public key */
        ret = mbedtls_mpi_read_binary(&session->ctx_client.Q.X,
                                      session->client_pubkey,
                                      PUBLIC_KEY_LEN);
        if (ret != 0) {
            ESP_LOGE(TAG, "Failed at mbedtls_mpi_read_binary with error code : %d", ret);
            goto abort_test_sec_endpoint;
        }
    }
    ret = mbedtls_mpi_write_binary(&session->ctx_client.Q.X,
                                   session->client_pubkey,
                                   PUBLIC_KEY_LEN);
    if (ret != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_mpi_write_binary with error code : %d", ret);
        goto abort_test_sec_endpoint;
    }
    flip_endian(session->client_pubkey, PUBLIC_KEY_LEN);

    /*********** Transaction0 = SessionCmd0 + SessionResp0 ****************/
    session_data__init(&req);
    if (prepare_command0(session, &req) != ESP_OK) {
        ESP_LOGE(TAG, "Failed in prepare_command0");
        goto abort_test_sec_endpoint;
    }

    inlen = session_data__get_packed_size(&req);
    inbuf = (uint8_t *) malloc(inlen);
    if (!inbuf) {
        ESP_LOGE(TAG, "Failed to allocate inbuf");
        goto abort_test_sec_endpoint;
    }

    session_data__pack(&req, inbuf);
    cleanup_command0(&req);

    outlen = 0;
    outbuf = NULL;
    ret = protocomm_req_handle(test_pc, "test-sec", session_id,
                               inbuf, inlen, &outbuf, &outlen);

    free(inbuf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "test-sec handler failed");
        free(outbuf);
        goto abort_test_sec_endpoint;
    }

    resp = session_data__unpack(NULL, outlen, outbuf);
    free(outbuf);
    if (!resp) {
        ESP_LOGE(TAG, "Unable to unpack SessionResp0");
        goto abort_test_sec_endpoint;
    }

    if (verify_response0(session, resp) != ESP_OK) {
        ESP_LOGE(TAG, "Invalid response 0");
        session_data__free_unpacked(resp, NULL);
        goto abort_test_sec_endpoint;
    }

    session_data__free_unpacked(resp, NULL);

    /*********** Transaction1 = SessionCmd1 + SessionResp1 ****************/
    session_data__init(&req);
    if (prepare_command1(session, &req) != ESP_OK) {
        ESP_LOGE(TAG, "Failed in prepare_command1");
        goto abort_test_sec_endpoint;
    }

    inlen = session_data__get_packed_size(&req);
    inbuf = (uint8_t *) malloc(inlen);
    if (!inbuf) {
        ESP_LOGE(TAG, "Failed to allocate inbuf");
        goto abort_test_sec_endpoint;
    }

    session_data__pack(&req, inbuf);
    cleanup_command1(&req);

    outlen = 0;
    outbuf = NULL;
    ret = protocomm_req_handle(test_pc, "test-sec", session_id,
                               inbuf, inlen, &outbuf, &outlen);

    free(inbuf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "test-sec handler failed");
        free(outbuf);
        goto abort_test_sec_endpoint;
    }

    resp = session_data__unpack(NULL, outlen, outbuf);
    free(outbuf);
    if (!resp) {
        ESP_LOGE(TAG, "Unable to unpack SessionResp0");
        goto abort_test_sec_endpoint;
    }

    if (verify_response1(session, resp) != ESP_OK) {
        ESP_LOGE(TAG, "Invalid response 1");
        session_data__free_unpacked(resp, NULL);
        goto abort_test_sec_endpoint;
    }

    session_data__free_unpacked(resp, NULL);
    mbedtls_ecdh_free(&session->ctx_client);
    mbedtls_ctr_drbg_free(&session->ctr_drbg);
    mbedtls_entropy_free(&session->entropy);

    return ESP_OK;

abort_test_sec_endpoint:

    mbedtls_ecdh_free(&session->ctx_client);
    mbedtls_ctr_drbg_free(&session->ctr_drbg);
    mbedtls_entropy_free(&session->entropy);
    return ESP_FAIL;
}