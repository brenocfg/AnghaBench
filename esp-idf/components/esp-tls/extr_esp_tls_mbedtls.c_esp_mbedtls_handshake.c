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
struct TYPE_6__ {int /*<<< orphan*/  conn_state; int /*<<< orphan*/  error_handle; int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ esp_tls_t ;
struct TYPE_7__ {int use_global_ca_store; int /*<<< orphan*/ * cacert_buf; } ;
typedef  TYPE_2__ esp_tls_cfg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_ESP ; 
 int /*<<< orphan*/  ERR_TYPE_MBEDTLS ; 
 int ESP_ERR_MBEDTLS_SSL_HANDSHAKE_FAILED ; 
 int /*<<< orphan*/  ESP_INT_EVENT_TRACKER_CAPTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_TLS_DONE ; 
 int ESP_TLS_ERR_SSL_WANT_READ ; 
 int ESP_TLS_ERR_SSL_WANT_WRITE ; 
 int /*<<< orphan*/  ESP_TLS_FAIL ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_mbedtls_verify_certificate (TYPE_1__*) ; 
 int mbedtls_ssl_handshake (int /*<<< orphan*/ *) ; 

int esp_mbedtls_handshake(esp_tls_t *tls, const esp_tls_cfg_t *cfg)
{
    int ret;
    ret = mbedtls_ssl_handshake(&tls->ssl);
    if (ret == 0) {
        tls->conn_state = ESP_TLS_DONE;
        return 1;
    } else {
        if (ret != ESP_TLS_ERR_SSL_WANT_READ && ret != ESP_TLS_ERR_SSL_WANT_WRITE) {
            ESP_LOGE(TAG, "mbedtls_ssl_handshake returned -0x%x", -ret);
            ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_MBEDTLS, -ret);
            ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_ESP, ESP_ERR_MBEDTLS_SSL_HANDSHAKE_FAILED);
            if (cfg->cacert_buf != NULL || cfg->use_global_ca_store == true) {
                /* This is to check whether handshake failed due to invalid certificate*/
                esp_mbedtls_verify_certificate(tls);
            }
            tls->conn_state = ESP_TLS_FAIL;
            return -1;
        }
        /* Irrespective of blocking or non-blocking I/O, we return on getting ESP_TLS_ERR_SSL_WANT_READ
        or ESP_TLS_ERR_SSL_WANT_WRITE during handshake */
        return 0;
    }
}