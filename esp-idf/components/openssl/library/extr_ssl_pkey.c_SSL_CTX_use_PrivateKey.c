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
struct TYPE_8__ {TYPE_2__* pkey; } ;
typedef  TYPE_2__ SSL_CTX ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_ASSERT1 (TYPE_2__*) ; 

int SSL_CTX_use_PrivateKey(SSL_CTX *ctx, EVP_PKEY *pkey)
{
    SSL_ASSERT1(ctx);
    SSL_ASSERT1(pkey);

    if (ctx->cert->pkey == pkey)
        return 1;

    if (ctx->cert->pkey)
        EVP_PKEY_free(ctx->cert->pkey);

    ctx->cert->pkey = pkey;

    return 1;
}