#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_cmac_context_t ;
struct TYPE_9__ {scalar_t__ cipher_ctx; TYPE_2__* cipher_info; struct TYPE_9__* cmac_ctx; } ;
typedef  TYPE_3__ mbedtls_cipher_context_t ;
struct TYPE_8__ {TYPE_1__* base; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* ctx_free_func ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void mbedtls_cipher_free( mbedtls_cipher_context_t *ctx )
{
    if( ctx == NULL )
        return;

#if defined(MBEDTLS_CMAC_C)
    if( ctx->cmac_ctx )
    {
       mbedtls_zeroize( ctx->cmac_ctx, sizeof( mbedtls_cmac_context_t ) );
       mbedtls_free( ctx->cmac_ctx );
    }
#endif

    if( ctx->cipher_ctx )
        ctx->cipher_info->base->ctx_free_func( ctx->cipher_ctx );

    mbedtls_zeroize( ctx, sizeof(mbedtls_cipher_context_t) );
}