#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_wolfssl_free_global_ca_store () ; 
 unsigned char* global_cacert ; 
 unsigned int global_cacert_pem_bytes ; 
 scalar_t__ strndup (char const*,unsigned int const) ; 

esp_err_t esp_wolfssl_set_global_ca_store(const unsigned char *cacert_pem_buf, const unsigned int cacert_pem_bytes)
{
    if (cacert_pem_buf == NULL) {
        ESP_LOGE(TAG, "cacert_pem_buf is null");
        return ESP_ERR_INVALID_ARG;
    }
    if (global_cacert != NULL) {
        esp_wolfssl_free_global_ca_store();
    }

    global_cacert = (unsigned char *)strndup((const char *)cacert_pem_buf, cacert_pem_bytes);
    if (!global_cacert) {
        return ESP_FAIL;
    }

    global_cacert_pem_bytes  = cacert_pem_bytes;

    return ESP_OK;
}