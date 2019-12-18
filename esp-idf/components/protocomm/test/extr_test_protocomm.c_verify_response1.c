#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/ * client_pubkey; int /*<<< orphan*/  stb; int /*<<< orphan*/  rand; int /*<<< orphan*/  nc_off; int /*<<< orphan*/  ctx_aes; int /*<<< orphan*/ * device_pubkey; } ;
typedef  TYPE_4__ session_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  check_buf ;
struct TYPE_14__ {TYPE_3__* sr1; } ;
struct TYPE_13__ {scalar_t__ proto_case; TYPE_1__* sec1; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_2__ device_verify_data; } ;
struct TYPE_9__ {scalar_t__ msg; } ;
typedef  TYPE_5__ SessionData ;
typedef  TYPE_6__ Sec1Payload ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int PUBLIC_KEY_LEN ; 
 scalar_t__ SEC1_MSG_TYPE__Session_Response1 ; 
 scalar_t__ SESSION_DATA__PROTO_SEC1 ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  hexdump (char*,int /*<<< orphan*/ *,int) ; 
 int mbedtls_aes_crypt_ctr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static esp_err_t verify_response1(session_t *session, SessionData *resp)
{
    uint8_t *cli_pubkey = session->client_pubkey;
    uint8_t *dev_pubkey = session->device_pubkey;

    hexdump("Device pubkey", dev_pubkey, PUBLIC_KEY_LEN);
    hexdump("Client pubkey", cli_pubkey, PUBLIC_KEY_LEN);

    if ((resp->proto_case != SESSION_DATA__PROTO_SEC1) ||
        (resp->sec1->msg  != SEC1_MSG_TYPE__Session_Response1)) {
        ESP_LOGE(TAG, "Invalid response type");
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t check_buf[PUBLIC_KEY_LEN];
    Sec1Payload *in = (Sec1Payload *) resp->sec1;

    int ret = mbedtls_aes_crypt_ctr(&session->ctx_aes, PUBLIC_KEY_LEN,
                                    &session->nc_off, session->rand, session->stb,
                                    in->sr1->device_verify_data.data, check_buf);
    if (ret != 0) {
        ESP_LOGE(TAG, "Failed at mbedtls_aes_crypt_ctr with erro code : %d", ret);
        return ESP_FAIL;
    }
    hexdump("Dec Device verifier", check_buf, sizeof(check_buf));

    if (memcmp(check_buf, session->client_pubkey, sizeof(session->client_pubkey)) != 0) {
        ESP_LOGE(TAG, "Key mismatch. Close connection");
        return ESP_FAIL;
    }

    return ESP_OK;
}