#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  entropy_context; int /*<<< orphan*/  ctr_drbg_context; int /*<<< orphan*/  ssl_config; int /*<<< orphan*/  ssl_context; int /*<<< orphan*/  own_cert; int /*<<< orphan*/  ca_cert; int /*<<< orphan*/  priv_key; } ;
typedef  TYPE_2__ TLSContext ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_ctr_drbg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_entropy_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_pk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_close_notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tls_close(URLContext *h)
{
    TLSContext *tls_ctx = h->priv_data;

    mbedtls_ssl_close_notify(&tls_ctx->ssl_context);
    mbedtls_pk_free(&tls_ctx->priv_key);
    mbedtls_x509_crt_free(&tls_ctx->ca_cert);
    mbedtls_x509_crt_free(&tls_ctx->own_cert);
    mbedtls_ssl_free(&tls_ctx->ssl_context);
    mbedtls_ssl_config_free(&tls_ctx->ssl_config);
    mbedtls_ctr_drbg_free(&tls_ctx->ctr_drbg_context);
    mbedtls_entropy_free(&tls_ctx->entropy_context);

    return 0;
}