#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * cacert_ptr; int /*<<< orphan*/  conf; } ;
typedef  TYPE_1__ esp_tls_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MBEDTLS_SSL_VERIFY_REQUIRED ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * global_cacert ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_authmode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_ca_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t set_global_ca_store(esp_tls_t *tls)
{
    assert(tls);
    if (global_cacert == NULL) {
        ESP_LOGE(TAG, "global_cacert is NULL");
        return ESP_ERR_INVALID_STATE;
    }
    tls->cacert_ptr = global_cacert;
    mbedtls_ssl_conf_authmode(&tls->conf, MBEDTLS_SSL_VERIFY_REQUIRED);
    mbedtls_ssl_conf_ca_chain(&tls->conf, tls->cacert_ptr, NULL);
    return ESP_OK;
}