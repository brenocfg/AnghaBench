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
struct TYPE_3__ {int /*<<< orphan*/  error_handle; scalar_t__ priv_ssl; } ;
typedef  TYPE_1__ esp_tls_t ;
typedef  int /*<<< orphan*/  WOLFSSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_WOLFSSL ; 
 int /*<<< orphan*/  ESP_INT_EVENT_TRACKER_CAPTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_TLS_ERR_SSL_WANT_READ ; 
 int /*<<< orphan*/  ESP_TLS_ERR_SSL_WANT_WRITE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  wolfSSL_get_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_write (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

ssize_t esp_wolfssl_write(esp_tls_t *tls, const char *data, size_t datalen)
{
    ssize_t ret = wolfSSL_write( (WOLFSSL *)tls->priv_ssl, (unsigned char *) data, datalen);
    if (ret < 0) {
        ret = wolfSSL_get_error( (WOLFSSL *)tls->priv_ssl, ret);
        if (ret != ESP_TLS_ERR_SSL_WANT_READ  && ret != ESP_TLS_ERR_SSL_WANT_WRITE) {
            ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_WOLFSSL, -ret);
            ESP_LOGE(TAG, "write error :%d:", ret);
        }
    }
    return ret;
}