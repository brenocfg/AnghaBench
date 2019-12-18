#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sockfd; void* priv_ssl; int /*<<< orphan*/  error_handle; void* priv_ctx; } ;
typedef  TYPE_1__ esp_tls_t ;
struct TYPE_6__ {int use_global_ca_store; int /*<<< orphan*/ * clientkey_pem_buf; int /*<<< orphan*/ * clientcert_pem_buf; int /*<<< orphan*/  clientkey_pem_bytes; int /*<<< orphan*/  clientcert_pem_bytes; scalar_t__ psk_hint_key; int /*<<< orphan*/  cacert_pem_bytes; int /*<<< orphan*/ * cacert_pem_buf; scalar_t__ alpn_protos; } ;
typedef  TYPE_2__ esp_tls_cfg_t ;
typedef  int /*<<< orphan*/  WOLFSSL_CTX ;
typedef  int /*<<< orphan*/  WOLFSSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_WOLFSSL ; 
 int /*<<< orphan*/  ESP_INT_EVENT_TRACKER_CAPTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_VERIFY_NONE ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WOLFSSL_ALPN_FAILED_ON_MISMATCH ; 
 int /*<<< orphan*/  WOLFSSL_FILETYPE_PEM ; 
 int WOLFSSL_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_wolfssl_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * global_cacert ; 
 int /*<<< orphan*/  global_cacert_pem_bytes ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strndup (char const*,size_t) ; 
 int /*<<< orphan*/  wolfSSL_CTX_load_verify_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wolfSSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_CTX_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_CTX_use_PrivateKey_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_CTX_use_certificate_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_Debugging_ON () ; 
 int wolfSSL_Init () ; 
 int wolfSSL_UseALPN (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wolfSSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_set_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_set_tlsext_host_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wolfTLSv1_2_client_method () ; 

int esp_create_wolfssl_handle(const char *hostname, size_t hostlen, const void *cfg1, esp_tls_t *tls)
{
#ifdef CONFIG_ESP_DEBUG_WOLFSSL
    wolfSSL_Debugging_ON();
#endif
    const esp_tls_cfg_t *cfg = cfg1;
    assert(cfg != NULL);
    assert(tls != NULL);

    int ret;
    ret = wolfSSL_Init();
    if (ret != WOLFSSL_SUCCESS) {
        ESP_LOGE(TAG, "Init wolfSSL failed: %d", ret);
        ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_WOLFSSL, -ret);
        goto exit;
    }

    tls->priv_ctx = (void *)wolfSSL_CTX_new(wolfTLSv1_2_client_method());
    if (!tls->priv_ctx) {
        ESP_LOGE(TAG, "Set wolfSSL ctx failed");
        ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_WOLFSSL, -ret);
        goto exit;
    }

#ifdef HAVE_ALPN
    if (cfg->alpn_protos) {
        char **alpn_list = (char **)cfg->alpn_protos;
        for (; *alpn_list != NULL; alpn_list ++) {
            if (wolfSSL_UseALPN( (WOLFSSL *)tls->priv_ssl, *alpn_list, strlen(*alpn_list), WOLFSSL_ALPN_FAILED_ON_MISMATCH) != WOLFSSL_SUCCESS) {
                ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_WOLFSSL, -ret);
                ESP_LOGE(TAG, "Use wolfSSL ALPN failed");
                goto exit;
            }
        }
    }
#endif

    if ( cfg->use_global_ca_store == true) {
        wolfSSL_CTX_load_verify_buffer( (WOLFSSL_CTX *)tls->priv_ctx, global_cacert, global_cacert_pem_bytes, WOLFSSL_FILETYPE_PEM);
        wolfSSL_CTX_set_verify( (WOLFSSL_CTX *)tls->priv_ctx, SSL_VERIFY_PEER, NULL);
    } else if (cfg->cacert_pem_buf != NULL) {
        wolfSSL_CTX_load_verify_buffer( (WOLFSSL_CTX *)tls->priv_ctx, cfg->cacert_pem_buf, cfg->cacert_pem_bytes, WOLFSSL_FILETYPE_PEM);
        wolfSSL_CTX_set_verify( (WOLFSSL_CTX *)tls->priv_ctx, SSL_VERIFY_PEER, NULL);
    } else if (cfg->psk_hint_key) {
        ESP_LOGE(TAG,"psk_hint_key not supported in wolfssl");
        goto exit;
    } else {
        wolfSSL_CTX_set_verify( (WOLFSSL_CTX *)tls->priv_ctx, SSL_VERIFY_NONE, NULL);
    }

    if (cfg->clientcert_pem_buf != NULL && cfg->clientkey_pem_buf != NULL) {
        wolfSSL_CTX_use_certificate_buffer( (WOLFSSL_CTX *)tls->priv_ctx, cfg->clientcert_pem_buf, cfg->clientcert_pem_bytes, WOLFSSL_FILETYPE_PEM);
        wolfSSL_CTX_use_PrivateKey_buffer( (WOLFSSL_CTX *)tls->priv_ctx, cfg->clientkey_pem_buf, cfg->clientkey_pem_bytes, WOLFSSL_FILETYPE_PEM);
    } else if (cfg->clientcert_pem_buf != NULL || cfg->clientkey_pem_buf != NULL) {
        ESP_LOGE(TAG, "You have to provide both clientcert_pem_buf and clientkey_pem_buf for mutual authentication\n\n");
        goto exit;
    }

    tls->priv_ssl =(void *)wolfSSL_new( (WOLFSSL_CTX *)tls->priv_ctx);
    if (!tls->priv_ssl) {
        ESP_LOGE(TAG, "Create wolfSSL failed");
        ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_WOLFSSL, -ret);
        goto exit;
    }

#ifdef HAVE_SNI
    /* Hostname set here should match CN in server certificate */
    char *use_host = strndup(hostname, hostlen);
    if (!use_host) {
        goto exit;
    }
    wolfSSL_set_tlsext_host_name( (WOLFSSL *)tls->priv_ssl, use_host);
    free(use_host);
#endif

    wolfSSL_set_fd((WOLFSSL *)tls->priv_ssl, tls->sockfd);
    return 0;
exit:
    esp_wolfssl_cleanup(tls);
    return ret;
}