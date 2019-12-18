#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ssl_pm {int /*<<< orphan*/  entropy; int /*<<< orphan*/  ctr_drbg; int /*<<< orphan*/  conf; int /*<<< orphan*/  fd; int /*<<< orphan*/  ssl; int /*<<< orphan*/  cl_fd; } ;
typedef  int /*<<< orphan*/  pers ;
struct TYPE_9__ {scalar_t__ version; struct ssl_pm* ssl_pm; TYPE_2__* ctx; TYPE_3__* method; } ;
struct TYPE_8__ {scalar_t__ endpoint; } ;
struct TYPE_6__ {scalar_t__ alpn_status; int /*<<< orphan*/  alpn_list; } ;
struct TYPE_7__ {TYPE_1__ ssl_alpn; int /*<<< orphan*/  read_buffer_len; } ;
typedef  TYPE_3__ SSL_METHOD ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 scalar_t__ ALPN_ENABLE ; 
 int /*<<< orphan*/  MBEDTLS_DEBUG_LEVEL ; 
 int MBEDTLS_SSL_IS_CLIENT ; 
 int MBEDTLS_SSL_IS_SERVER ; 
 int /*<<< orphan*/  MBEDTLS_SSL_MAJOR_VERSION_3 ; 
 int MBEDTLS_SSL_MINOR_VERSION_0 ; 
 int MBEDTLS_SSL_MINOR_VERSION_1 ; 
 int MBEDTLS_SSL_MINOR_VERSION_2 ; 
 int MBEDTLS_SSL_MINOR_VERSION_3 ; 
 int /*<<< orphan*/  MBEDTLS_SSL_PRESET_DEFAULT ; 
 int /*<<< orphan*/  MBEDTLS_SSL_TRANSPORT_STREAM ; 
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_PLATFORM_ERROR_LEVEL ; 
 scalar_t__ TLS1_1_VERSION ; 
 scalar_t__ TLS1_2_VERSION ; 
 scalar_t__ TLS1_VERSION ; 
 scalar_t__ TLS_ANY_VERSION ; 
 int /*<<< orphan*/  max_content_len ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_random ; 
 int mbedtls_ctr_drbg_seed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_debug_set_threshold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_entropy_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_entropy_func ; 
 int /*<<< orphan*/  mbedtls_entropy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_net_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_net_recv ; 
 int /*<<< orphan*/  mbedtls_net_send ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_alpn_protocols (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_dbg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_max_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_min_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_rng (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mbedtls_ssl_config_defaults (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ssl_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mbedtls_ssl_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_mem_free (struct ssl_pm*) ; 
 struct ssl_pm* ssl_mem_zalloc (int) ; 
 int /*<<< orphan*/ * ssl_platform_debug ; 

int ssl_pm_new(SSL *ssl)
{
    struct ssl_pm *ssl_pm;
    int ret;

    const unsigned char pers[] = "OpenSSL PM";
    size_t pers_len = sizeof(pers);

    int endpoint;
    int version;

    const SSL_METHOD *method = ssl->method;

    ssl_pm = ssl_mem_zalloc(sizeof(struct ssl_pm));
    if (!ssl_pm) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "no enough memory > (ssl_pm)");
        goto no_mem;
    }

    max_content_len = ssl->ctx->read_buffer_len;

    mbedtls_net_init(&ssl_pm->fd);
    mbedtls_net_init(&ssl_pm->cl_fd);

    mbedtls_ssl_config_init(&ssl_pm->conf);
    mbedtls_ctr_drbg_init(&ssl_pm->ctr_drbg);
    mbedtls_entropy_init(&ssl_pm->entropy);
    mbedtls_ssl_init(&ssl_pm->ssl);

    ret = mbedtls_ctr_drbg_seed(&ssl_pm->ctr_drbg, mbedtls_entropy_func, &ssl_pm->entropy, pers, pers_len);
    if (ret) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "mbedtls_ctr_drbg_seed() return -0x%x", -ret);
        goto mbedtls_err1;
    }

    if (method->endpoint) {
        endpoint = MBEDTLS_SSL_IS_SERVER;
    } else {
        endpoint = MBEDTLS_SSL_IS_CLIENT;
    }
    ret = mbedtls_ssl_config_defaults(&ssl_pm->conf, endpoint, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT);
    if (ret) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "mbedtls_ssl_config_defaults() return -0x%x", -ret);
        goto mbedtls_err2;
    }

    if (TLS_ANY_VERSION != ssl->version) {
        if (TLS1_2_VERSION == ssl->version)
            version = MBEDTLS_SSL_MINOR_VERSION_3;
        else if (TLS1_1_VERSION == ssl->version)
            version = MBEDTLS_SSL_MINOR_VERSION_2;
        else if (TLS1_VERSION == ssl->version)
            version = MBEDTLS_SSL_MINOR_VERSION_1;
        else
            version = MBEDTLS_SSL_MINOR_VERSION_0;

        mbedtls_ssl_conf_max_version(&ssl_pm->conf, MBEDTLS_SSL_MAJOR_VERSION_3, version);
        mbedtls_ssl_conf_min_version(&ssl_pm->conf, MBEDTLS_SSL_MAJOR_VERSION_3, version);
    } else {
        mbedtls_ssl_conf_max_version(&ssl_pm->conf, MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_3);
        mbedtls_ssl_conf_min_version(&ssl_pm->conf, MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_0);
    }

    if (ssl->ctx->ssl_alpn.alpn_status == ALPN_ENABLE) {
#ifdef MBEDTLS_SSL_ALPN
        mbedtls_ssl_conf_alpn_protocols( &ssl_pm->conf, ssl->ctx->ssl_alpn.alpn_list );
#else
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "CONFIG_MBEDTLS_SSL_ALPN must be enabled to use ALPN", -1);
#endif // MBEDTLS_SSL_ALPN
    }
    mbedtls_ssl_conf_rng(&ssl_pm->conf, mbedtls_ctr_drbg_random, &ssl_pm->ctr_drbg);

#ifdef CONFIG_OPENSSL_LOWLEVEL_DEBUG
    mbedtls_debug_set_threshold(MBEDTLS_DEBUG_LEVEL);
    mbedtls_ssl_conf_dbg(&ssl_pm->conf, ssl_platform_debug, NULL);
#else
    mbedtls_ssl_conf_dbg(&ssl_pm->conf, NULL, NULL);
#endif

    ret = mbedtls_ssl_setup(&ssl_pm->ssl, &ssl_pm->conf);
    if (ret) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "mbedtls_ssl_setup() return -0x%x", -ret);
        goto mbedtls_err2;
    }

    mbedtls_ssl_set_bio(&ssl_pm->ssl, &ssl_pm->fd, mbedtls_net_send, mbedtls_net_recv, NULL);

    ssl->ssl_pm = ssl_pm;

    return 0;

mbedtls_err2:
    mbedtls_ssl_config_free(&ssl_pm->conf);
    mbedtls_ctr_drbg_free(&ssl_pm->ctr_drbg);
mbedtls_err1:
    mbedtls_entropy_free(&ssl_pm->entropy);
    ssl_mem_free(ssl_pm);
no_mem:
    return -1;
}