#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int ssize_t ;
struct TYPE_3__ {int sec_ver; int /*<<< orphan*/  stb; int /*<<< orphan*/  rand; int /*<<< orphan*/  nc_off; int /*<<< orphan*/  ctx_aes; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ session_t ;
typedef  int /*<<< orphan*/  rand_test_data ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  enc_test_data ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getrandom (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexdump (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  mbedtls_aes_crypt_ctr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ protocomm_req_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  test_pc ; 

__attribute__((used)) static esp_err_t test_req_endpoint(session_t *session)
{
    uint32_t session_id = session->id;

    uint8_t rand_test_data[512], enc_test_data[512];
    getrandom(rand_test_data, sizeof(rand_test_data), 0);

    if (session->sec_ver == 0) {
        memcpy(enc_test_data, rand_test_data, sizeof(rand_test_data));
    }
    else if (session->sec_ver == 1) {
        mbedtls_aes_crypt_ctr(&session->ctx_aes, sizeof(rand_test_data), &session->nc_off,
                              session->rand, session->stb, rand_test_data, enc_test_data);
    }

    ssize_t  verify_data_len = 0;
    uint8_t *enc_verify_data = NULL;

    esp_err_t ret = protocomm_req_handle(test_pc, "test-ep", session_id,
                                         enc_test_data, sizeof(enc_test_data),
                                         &enc_verify_data, &verify_data_len);

    if (ret != ESP_OK || !verify_data_len) {
        ESP_LOGE(TAG, "test-ep handler failed");
        return ESP_FAIL;
    }

    uint8_t *verify_data = malloc(verify_data_len);
    if (!verify_data) {
        ESP_LOGE(TAG, "error allocating memory for decrypted data");
        free(enc_verify_data);
        return ESP_FAIL;
    }

    if (session->sec_ver == 0) {
        memcpy(verify_data, enc_verify_data, verify_data_len);
    }
    else if (session->sec_ver == 1) {
        mbedtls_aes_crypt_ctr(&session->ctx_aes, verify_data_len, &session->nc_off,
                              session->rand, session->stb, enc_verify_data, verify_data);
    }
    free(enc_verify_data);

    hexdump("Sent data", rand_test_data, sizeof(rand_test_data));
    hexdump("Recv data", verify_data,    verify_data_len);

    ESP_LOGI(TAG, "verify data len   : %d", verify_data_len);
    ESP_LOGI(TAG, "expected data len : %d", sizeof(rand_test_data));

    if (verify_data_len != sizeof(rand_test_data)) {
        ESP_LOGE(TAG, "incorrect response length from test-ep");
        free(verify_data);
        return ESP_FAIL;
    }
    if (memcmp(rand_test_data, verify_data, verify_data_len)) {
        ESP_LOGE(TAG, "incorrect response data from test-ep");
        free(verify_data);
        return ESP_FAIL;
    }
    free(verify_data);
    return ESP_OK;
}