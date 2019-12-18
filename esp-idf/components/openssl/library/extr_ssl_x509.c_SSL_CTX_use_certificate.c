#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* cert; } ;
typedef  TYPE_2__ X509 ;
struct TYPE_8__ {TYPE_2__* x509; } ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT1 (TYPE_2__*) ; 
 int /*<<< orphan*/  X509_free (TYPE_2__*) ; 

int SSL_CTX_use_certificate(SSL_CTX *ctx, X509 *x)
{
    SSL_ASSERT1(ctx);
    SSL_ASSERT1(x);

    if (ctx->cert->x509 == x)
        return 1;

    X509_free(ctx->cert->x509);

    ctx->cert->x509 = x;

    return 1;
}