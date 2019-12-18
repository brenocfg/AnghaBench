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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {int /*<<< orphan*/  version; int /*<<< orphan*/ * cert; int /*<<< orphan*/ * client_CA; TYPE_1__ const* method; } ;
struct TYPE_5__ {int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ SSL_METHOD ;
typedef  TYPE_2__ SSL_CTX ;
typedef  int /*<<< orphan*/  CERT ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SSL_LIB_ERROR_LEVEL ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_new () ; 
 int /*<<< orphan*/  ssl_cert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ssl_cert_new () ; 
 scalar_t__ ssl_mem_zalloc (int) ; 

SSL_CTX* SSL_CTX_new(const SSL_METHOD *method)
{
    SSL_CTX *ctx;
    CERT *cert;
    X509 *client_ca;

    if (!method) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "no no_method");
        return NULL;
    }

    client_ca = X509_new();
    if (!client_ca) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "X509_new() return NULL");
        goto failed1;
    }

    cert = ssl_cert_new();
    if (!cert) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "ssl_cert_new() return NULL");
        goto failed2;
    }

    ctx = (SSL_CTX *)ssl_mem_zalloc(sizeof(SSL_CTX));
    if (!ctx) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "no enough memory > (ctx)");
        goto failed3;
    }

    ctx->method = method;
    ctx->client_CA = client_ca;
    ctx->cert = cert;

    ctx->version = method->version;

    return ctx;

failed3:
    ssl_cert_free(cert);
failed2:
    X509_free(client_ca);
failed1:
    return NULL;
}