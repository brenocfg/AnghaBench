#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  char const* ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/  sec_inst; TYPE_1__* sec; } ;
typedef  TYPE_2__ protocomm_t ;
struct TYPE_9__ {int flag; int /*<<< orphan*/  priv_data; scalar_t__ (* req_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const**,char const**,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ protocomm_ep_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_7__ {scalar_t__ (* encrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*,char const**) ;scalar_t__ (* decrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*,char const**) ;} ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_NOT_FOUND ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int REQ_EP ; 
 int SEC_EP ; 
 int /*<<< orphan*/  TAG ; 
 int VER_EP ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/  const*) ; 
 scalar_t__ malloc (char const*) ; 
 TYPE_3__* search_endpoint (TYPE_2__*,char const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const**,char const**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*,char const**) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const**,char const**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*,char const**) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const**,char const**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const**,char const**,int /*<<< orphan*/ ) ; 

esp_err_t protocomm_req_handle(protocomm_t *pc, const char *ep_name, uint32_t session_id,
                               const uint8_t *inbuf, ssize_t inlen,
                               uint8_t **outbuf, ssize_t *outlen)
{
    if (!pc || !ep_name || !outbuf || !outlen) {
        ESP_LOGE(TAG, "Invalid params %p %p", pc, ep_name);
        return ESP_ERR_INVALID_ARG;
    }

    *outbuf = NULL;
    *outlen = 0;

    protocomm_ep_t *ep = search_endpoint(pc, ep_name);
    if (!ep) {
        ESP_LOGE(TAG, "No registered endpoint for %s", ep_name);
        return ESP_ERR_NOT_FOUND;
    }

    esp_err_t ret = ESP_FAIL;
    if (ep->flag & SEC_EP) {
        /* Call the registered endpoint handler for establishing secure session */
        ret = ep->req_handler(session_id, inbuf, inlen, outbuf, outlen, ep->priv_data);
        ESP_LOGD(TAG, "SEC_EP Req handler returned %d", ret);
    } else if (ep->flag & REQ_EP) {
        if (pc->sec && pc->sec->decrypt) {
            /* Decrypt the data first */
            uint8_t *dec_inbuf = (uint8_t *) malloc(inlen);
            if (!dec_inbuf) {
                ESP_LOGE(TAG, "Failed to allocate decrypt buf len %d", inlen);
                return ESP_ERR_NO_MEM;
            }

            ssize_t dec_inbuf_len = inlen;
            ret = pc->sec->decrypt(pc->sec_inst, session_id, inbuf, inlen, dec_inbuf, &dec_inbuf_len);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "Decryption of response failed for endpoint %s", ep_name);
                free(dec_inbuf);
                return ret;
            }

            /* Invoke the request handler */
            uint8_t *plaintext_resp = NULL;
            ssize_t plaintext_resp_len = 0;
            ret = ep->req_handler(session_id,
                                  dec_inbuf, dec_inbuf_len,
                                  &plaintext_resp, &plaintext_resp_len,
                                  ep->priv_data);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "Request handler for %s failed", ep_name);
                free(plaintext_resp);
                free(dec_inbuf);
                return ret;
            }
            /* We don't need decrypted data anymore */
            free(dec_inbuf);

            /* Encrypt response to be sent back */
            uint8_t *enc_resp = (uint8_t *) malloc(plaintext_resp_len);
            if (!enc_resp) {
                ESP_LOGE(TAG, "Failed to allocate decrypt buf len %d", inlen);
                free(plaintext_resp);
                return ESP_ERR_NO_MEM;
            }

            ssize_t enc_resp_len = plaintext_resp_len;
            ret = pc->sec->encrypt(pc->sec_inst, session_id, plaintext_resp, plaintext_resp_len,
                                   enc_resp, &enc_resp_len);

            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "Encryption of response failed for endpoint %s", ep_name);
                free(enc_resp);
                free(plaintext_resp);
                return ret;
            }

            /* We no more need plaintext response */
            free(plaintext_resp);

            /* Set outbuf and outlen appropriately */
            *outbuf = enc_resp;
            *outlen = enc_resp_len;
        } else {
            /* No encryption */
            ret = ep->req_handler(session_id,
                                  inbuf, inlen,
                                  outbuf, outlen,
                                  ep->priv_data);
            ESP_LOGD(TAG, "No encrypt ret %d", ret);
        }
    } else if (ep->flag & VER_EP) {
        ret = ep->req_handler(session_id, inbuf, inlen, outbuf, outlen, ep->priv_data);
        ESP_LOGD(TAG, "VER_EP Req handler returned %d", ret);
    }
    return ret;
}