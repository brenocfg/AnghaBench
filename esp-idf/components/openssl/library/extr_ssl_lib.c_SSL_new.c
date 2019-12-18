#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  session; int /*<<< orphan*/  cert; int /*<<< orphan*/  client_CA; int /*<<< orphan*/  rwstate; int /*<<< orphan*/  verify_mode; int /*<<< orphan*/  options; int /*<<< orphan*/  version; int /*<<< orphan*/  method; TYPE_1__* ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  verify_mode; int /*<<< orphan*/  options; int /*<<< orphan*/  version; int /*<<< orphan*/  method; int /*<<< orphan*/  client_CA; int /*<<< orphan*/  cert; } ;
typedef  TYPE_1__ SSL_CTX ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_LIB_ERROR_LEVEL ; 
 int SSL_METHOD_CALL (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_NOTHING ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_SESSION_new () ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __X509_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ssl_cert_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new ; 
 int /*<<< orphan*/  ssl_cert_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_mem_free (TYPE_2__*) ; 
 scalar_t__ ssl_mem_zalloc (int) ; 

SSL *SSL_new(SSL_CTX *ctx)
{
    int ret = 0;
    SSL *ssl;

    if (!ctx) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "no ctx");
        return NULL;
    }

    ssl = (SSL *)ssl_mem_zalloc(sizeof(SSL));
    if (!ssl) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "no enough memory > (ssl)");
        goto failed1;
    }

    ssl->session = SSL_SESSION_new();
    if (!ssl->session) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "SSL_SESSION_new() return NULL");
        goto failed2;
    }

    ssl->cert = __ssl_cert_new(ctx->cert);
    if (!ssl->cert) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "__ssl_cert_new() return NULL");
        goto failed3;
    }

    ssl->client_CA = __X509_new(ctx->client_CA);
    if (!ssl->client_CA) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "__X509_new() return NULL");
        goto failed4;
    }

    ssl->ctx = ctx;
    ssl->method = ctx->method;

    ssl->version = ctx->version;
    ssl->options = ctx->options;

    ssl->verify_mode = ctx->verify_mode;

    ret = SSL_METHOD_CALL(new, ssl);
    if (ret) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "SSL_METHOD_CALL(new) return %d", ret);
        goto failed5;
    }

    ssl->rwstate = SSL_NOTHING;

    return ssl;

failed5:
    X509_free(ssl->client_CA);
failed4:
    ssl_cert_free(ssl->cert);
failed3:
    SSL_SESSION_free(ssl->session);
failed2:
    ssl_mem_free(ssl);
failed1:
    return NULL;
}