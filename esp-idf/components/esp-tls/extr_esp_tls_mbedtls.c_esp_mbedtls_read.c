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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  error_handle; int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ esp_tls_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_MBEDTLS ; 
 int /*<<< orphan*/  ESP_INT_EVENT_TRACKER_CAPTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_TLS_ERR_SSL_WANT_READ ; 
 int /*<<< orphan*/  ESP_TLS_ERR_SSL_WANT_WRITE ; 
 int /*<<< orphan*/  MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  mbedtls_ssl_read (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

ssize_t esp_mbedtls_read(esp_tls_t *tls, char *data, size_t datalen)
{

    ssize_t ret = mbedtls_ssl_read(&tls->ssl, (unsigned char *)data, datalen);
    if (ret < 0) {
        if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
            return 0;
        }
        if (ret != ESP_TLS_ERR_SSL_WANT_READ  && ret != ESP_TLS_ERR_SSL_WANT_WRITE) {
            ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_MBEDTLS, -ret);
            ESP_LOGE(TAG, "read error :%d:", ret);
        }
    }
    return ret;
}