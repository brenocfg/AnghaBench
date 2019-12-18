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
struct TYPE_3__ {int /*<<< orphan*/  error_handle; int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ esp_tls_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_MBEDTLS_CERT_FLAGS ; 
 int /*<<< orphan*/  ESP_INT_EVENT_TRACKER_CAPTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int mbedtls_ssl_get_verify_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_verify_info (char*,int,char*,int) ; 

void esp_mbedtls_verify_certificate(esp_tls_t *tls)
{
    int flags;
    char buf[100];
    if ((flags = mbedtls_ssl_get_verify_result(&tls->ssl)) != 0) {
        ESP_LOGI(TAG, "Failed to verify peer certificate!");
        ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_MBEDTLS_CERT_FLAGS, flags);
        bzero(buf, sizeof(buf));
        mbedtls_x509_crt_verify_info(buf, sizeof(buf), "  ! ", flags);
        ESP_LOGI(TAG, "verification info: %s", buf);
    } else {
        ESP_LOGI(TAG, "Certificate verified.");
    }
}