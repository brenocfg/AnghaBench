#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {scalar_t__ role; TYPE_4__ server_fd; int /*<<< orphan*/  ssl; int /*<<< orphan*/  error_handle; int /*<<< orphan*/  conf; int /*<<< orphan*/  ctr_drbg; int /*<<< orphan*/  entropy; int /*<<< orphan*/  sockfd; } ;
typedef  TYPE_1__ esp_tls_t ;
typedef  int /*<<< orphan*/  esp_tls_cfg_t ;
typedef  int /*<<< orphan*/  esp_tls_cfg_server_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MBEDTLS_DEBUG_LEVEL ; 
 int /*<<< orphan*/  ERR_TYPE_MBEDTLS ; 
 scalar_t__ ESP_ERR_MBEDTLS_CTR_DRBG_SEED_FAILED ; 
 scalar_t__ ESP_ERR_MBEDTLS_SSL_SETUP_FAILED ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_INT_EVENT_TRACKER_CAPTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ ESP_TLS_CLIENT ; 
 scalar_t__ ESP_TLS_SERVER ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_mbedtls_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_random ; 
 int mbedtls_ctr_drbg_seed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_entropy_func ; 
 int /*<<< orphan*/  mbedtls_entropy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_esp_enable_debug_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_net_recv ; 
 int /*<<< orphan*/  mbedtls_net_send ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_rng (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_set_bio (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mbedtls_ssl_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ set_client_config (char const*,size_t,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ set_server_config (int /*<<< orphan*/ *,TYPE_1__*) ; 

esp_err_t esp_create_mbedtls_handle(const char *hostname, size_t hostlen, const void *cfg, esp_tls_t *tls)
{
    assert(cfg != NULL);
    assert(tls != NULL);
    int ret;
    esp_err_t esp_ret = ESP_FAIL;
    tls->server_fd.fd = tls->sockfd;
    mbedtls_ssl_init(&tls->ssl);
    mbedtls_ctr_drbg_init(&tls->ctr_drbg);
    mbedtls_ssl_config_init(&tls->conf);
    mbedtls_entropy_init(&tls->entropy);

    if (tls->role == ESP_TLS_CLIENT) {
        esp_ret = set_client_config(hostname, hostlen, (esp_tls_cfg_t *)cfg, tls);
        if (esp_ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to set client configurations");
            goto exit;
        }
    } else if (tls->role == ESP_TLS_SERVER) {
#ifdef CONFIG_ESP_TLS_SERVER
        esp_ret = set_server_config((esp_tls_cfg_server_t *) cfg, tls);
        if (esp_ret != 0) {
            ESP_LOGE(TAG, "Failed to set server configurations");
            goto exit;
        }
#else
            ESP_LOGE(TAG, "ESP_TLS_SERVER Not enabled in Kconfig");
            goto exit;
#endif
    }

    if ((ret = mbedtls_ctr_drbg_seed(&tls->ctr_drbg,
                                     mbedtls_entropy_func, &tls->entropy, NULL, 0)) != 0) {
        ESP_LOGE(TAG, "mbedtls_ctr_drbg_seed returned -0x%x", -ret);
        ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_MBEDTLS, -ret);
        esp_ret = ESP_ERR_MBEDTLS_CTR_DRBG_SEED_FAILED;
        goto exit;
    }

    mbedtls_ssl_conf_rng(&tls->conf, mbedtls_ctr_drbg_random, &tls->ctr_drbg);

#ifdef CONFIG_MBEDTLS_DEBUG
    mbedtls_esp_enable_debug_log(&tls->conf, CONFIG_MBEDTLS_DEBUG_LEVEL);
#endif

    if ((ret = mbedtls_ssl_setup(&tls->ssl, &tls->conf)) != 0) {
        ESP_LOGE(TAG, "mbedtls_ssl_setup returned -0x%x", -ret);
        ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_MBEDTLS, -ret);
        esp_ret = ESP_ERR_MBEDTLS_SSL_SETUP_FAILED;
        goto exit;
    }
    mbedtls_ssl_set_bio(&tls->ssl, &tls->server_fd, mbedtls_net_send, mbedtls_net_recv, NULL);

    return ESP_OK;

exit:
    esp_mbedtls_cleanup(tls);
    return esp_ret;

}