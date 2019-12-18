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
struct TYPE_5__ {int verbose; int /*<<< orphan*/  errorbio; int /*<<< orphan*/  curl; int /*<<< orphan*/  accesstype; } ;
typedef  TYPE_1__ sslctxparm ;
struct TYPE_6__ {scalar_t__ cert; } ;
typedef  TYPE_2__ X509_STORE_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  NID_info_access ; 
 int /*<<< orphan*/  NID_sinfo_access ; 
 int /*<<< orphan*/  X509_print_ex (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_verify_cert (TYPE_2__*) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 unsigned char* my_get_ext (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_app_verify_callback(X509_STORE_CTX *ctx, void *arg)
{
  sslctxparm * p = (sslctxparm *) arg;
  int ok;

  if(p->verbose > 2)
    BIO_printf(p->errorbio, "entering ssl_app_verify_callback\n");

  ok = X509_verify_cert(ctx);
  if(ok && ctx->cert) {
    unsigned char *accessinfo;
    if(p->verbose > 1)
      X509_print_ex(p->errorbio, ctx->cert, 0, 0);

    accessinfo = my_get_ext(ctx->cert, p->accesstype, NID_sinfo_access);
    if(accessinfo) {
      if(p->verbose)
        BIO_printf(p->errorbio, "Setting URL from SIA to: %s\n", accessinfo);

      curl_easy_setopt(p->curl, CURLOPT_URL, accessinfo);
    }
    else if(accessinfo = my_get_ext(ctx->cert, p->accesstype,
                                    NID_info_access)) {
      if(p->verbose)
        BIO_printf(p->errorbio, "Setting URL from AIA to: %s\n", accessinfo);

      curl_easy_setopt(p->curl, CURLOPT_URL, accessinfo);
    }
  }
  if(p->verbose > 2)
    BIO_printf(p->errorbio, "leaving ssl_app_verify_callback with %d\n", ok);

  return ok;
}