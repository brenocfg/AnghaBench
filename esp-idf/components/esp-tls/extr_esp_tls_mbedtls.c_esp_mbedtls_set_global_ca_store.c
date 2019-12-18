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
typedef  int esp_err_t ;

/* Variables and functions */
 int ESP_ERR_INVALID_ARG ; 
 int ESP_ERR_MBEDTLS_CERT_PARTLY_OK ; 
 int ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int esp_mbedtls_init_global_ca_store () ; 
 int /*<<< orphan*/ * global_cacert ; 
 int /*<<< orphan*/  mbedtls_x509_crt_free (int /*<<< orphan*/ *) ; 
 int mbedtls_x509_crt_parse (int /*<<< orphan*/ *,unsigned char const*,unsigned int const) ; 

esp_err_t esp_mbedtls_set_global_ca_store(const unsigned char *cacert_pem_buf, const unsigned int cacert_pem_bytes)
{
    if (cacert_pem_buf == NULL) {
        ESP_LOGE(TAG, "cacert_pem_buf is null");
        return ESP_ERR_INVALID_ARG;
    }
    int ret;
    if (global_cacert == NULL) {
        ret = esp_mbedtls_init_global_ca_store();
        if (ret != ESP_OK) {
            return ret;
        }
    }
    ret = mbedtls_x509_crt_parse(global_cacert, cacert_pem_buf, cacert_pem_bytes);
    if (ret < 0) {
        ESP_LOGE(TAG, "mbedtls_x509_crt_parse returned -0x%x", -ret);
        mbedtls_x509_crt_free(global_cacert);
        global_cacert = NULL;
        return ESP_FAIL;
    } else if (ret > 0) {
        ESP_LOGE(TAG, "mbedtls_x509_crt_parse was partly successful. No. of failed certificates: %d", ret);
        return ESP_ERR_MBEDTLS_CERT_PARTLY_OK;
    }
    return ESP_OK;
}