#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  conn_state; int /*<<< orphan*/  error_handle; scalar_t__ priv_ssl; } ;
typedef  TYPE_1__ esp_tls_t ;
struct TYPE_7__ {int use_global_ca_store; int /*<<< orphan*/ * cacert_pem_buf; } ;
typedef  TYPE_2__ esp_tls_cfg_t ;
typedef  int /*<<< orphan*/  WOLFSSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_WOLFSSL ; 
 int /*<<< orphan*/  ESP_INT_EVENT_TRACKER_CAPTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_TLS_DONE ; 
 int ESP_TLS_ERR_SSL_WANT_READ ; 
 int ESP_TLS_ERR_SSL_WANT_WRITE ; 
 int /*<<< orphan*/  ESP_TLS_FAIL ; 
 int /*<<< orphan*/  TAG ; 
 int WOLFSSL_SUCCESS ; 
 int /*<<< orphan*/  esp_wolfssl_verify_certificate (TYPE_1__*) ; 
 int wolfSSL_connect (int /*<<< orphan*/ *) ; 
 int wolfSSL_get_error (int /*<<< orphan*/ *,int) ; 

int esp_wolfssl_handshake(esp_tls_t *tls, const esp_tls_cfg_t *cfg)
{
    int ret;
    ret = wolfSSL_connect( (WOLFSSL *)tls->priv_ssl);
    if (ret == WOLFSSL_SUCCESS) {
        tls->conn_state = ESP_TLS_DONE;
        return 1;
    } else {
        int err = wolfSSL_get_error( (WOLFSSL *)tls->priv_ssl, ret);
        if (err != ESP_TLS_ERR_SSL_WANT_READ && err != ESP_TLS_ERR_SSL_WANT_WRITE) {
            ESP_LOGE(TAG, "wolfSSL_connect returned -0x%x", -ret);
            ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_WOLFSSL, -ret);

            if (cfg->cacert_pem_buf != NULL || cfg->use_global_ca_store == true) {
                /* This is to check whether handshake failed due to invalid certificate*/
                esp_wolfssl_verify_certificate(tls);
            }
            tls->conn_state = ESP_TLS_FAIL;
            return -1;
        }
        /* Irrespective of blocking or non-blocking I/O, we return on getting wolfSSL_want_read
        or wolfSSL_want_write during handshake */
        return 0;
    }
}