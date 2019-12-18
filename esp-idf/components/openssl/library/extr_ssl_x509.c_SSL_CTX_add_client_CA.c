#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* client_CA; } ;
typedef  TYPE_1__ X509 ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT1 (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_free (TYPE_1__*) ; 

int SSL_CTX_add_client_CA(SSL_CTX *ctx, X509 *x)
{
    SSL_ASSERT1(ctx);
    SSL_ASSERT1(x);

    if (ctx->client_CA == x)
        return 1;

    X509_free(ctx->client_CA);

    ctx->client_CA = x;

    return 1;
}