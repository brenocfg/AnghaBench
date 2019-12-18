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
struct TYPE_3__ {int /*<<< orphan*/  error_handle; scalar_t__ priv_ssl; } ;
typedef  TYPE_1__ esp_tls_t ;
typedef  int /*<<< orphan*/  WOLFSSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_WOLFSSL_CERT_FLAGS ; 
 int /*<<< orphan*/  ESP_INT_EVENT_TRACKER_CAPTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int WOLFSSL_SUCCESS ; 
 int wolfSSL_get_verify_result (int /*<<< orphan*/ *) ; 

void esp_wolfssl_verify_certificate(esp_tls_t *tls)
{
    int flags;
    if ((flags = wolfSSL_get_verify_result( (WOLFSSL *)tls->priv_ssl)) != WOLFSSL_SUCCESS) {
        ESP_LOGE(TAG, "Failed to verify peer certificate %d!", flags);
        ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_WOLFSSL_CERT_FLAGS, flags);
    } else {
        ESP_LOGI(TAG, "Certificate verified.");
    }
}