#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  errorbio; int /*<<< orphan*/  ca; int /*<<< orphan*/  pkey; int /*<<< orphan*/  usercert; } ;
typedef  TYPE_1__ sslctxparm ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_SSL_CERTPROBLEM ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_check_private_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_get_cert_store (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_cert_verify_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_CTX_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_quiet_shutdown (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify_depth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_MODE_AUTO_RETRY ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  X509_STORE_add_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO_NULL ; 
 scalar_t__ sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ssl_app_verify_callback ; 

__attribute__((used)) static CURLcode sslctxfun(CURL *curl, void *sslctx, void *parm)
{
  sslctxparm *p = (sslctxparm *) parm;
  SSL_CTX *ctx = (SSL_CTX *) sslctx;

  if(!SSL_CTX_use_certificate(ctx, p->usercert)) {
    BIO_printf(p->errorbio, "SSL_CTX_use_certificate problem\n");
    goto err;
  }
  if(!SSL_CTX_use_PrivateKey(ctx, p->pkey)) {
    BIO_printf(p->errorbio, "SSL_CTX_use_PrivateKey\n");
    goto err;
  }

  if(!SSL_CTX_check_private_key(ctx)) {
    BIO_printf(p->errorbio, "SSL_CTX_check_private_key\n");
    goto err;
  }

  SSL_CTX_set_quiet_shutdown(ctx, 1);
  SSL_CTX_set_cipher_list(ctx, "RC4-MD5");
  SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);

  X509_STORE_add_cert(SSL_CTX_get_cert_store(ctx),
                      sk_X509_value(p->ca, sk_X509_num(p->ca)-1));

  SSL_CTX_set_verify_depth(ctx, 2);
  SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, ZERO_NULL);
  SSL_CTX_set_cert_verify_callback(ctx, ssl_app_verify_callback, parm);

  return CURLE_OK;
  err:
  ERR_print_errors(p->errorbio);
  return CURLE_SSL_CERTPROBLEM;

}