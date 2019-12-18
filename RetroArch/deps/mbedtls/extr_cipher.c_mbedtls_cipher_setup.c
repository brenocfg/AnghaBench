#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* base; } ;
typedef  TYPE_2__ mbedtls_cipher_info_t ;
struct TYPE_10__ {TYPE_2__ const* cipher_info; int /*<<< orphan*/ * cipher_ctx; } ;
typedef  TYPE_3__ mbedtls_cipher_context_t ;
struct TYPE_8__ {int /*<<< orphan*/ * (* ctx_alloc_func ) () ;} ;

/* Variables and functions */
 int MBEDTLS_ERR_CIPHER_ALLOC_FAILED ; 
 int MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_PADDING_NONE ; 
 int /*<<< orphan*/  MBEDTLS_PADDING_PKCS7 ; 
 int /*<<< orphan*/  mbedtls_cipher_set_padding_mode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * stub1 () ; 

int mbedtls_cipher_setup( mbedtls_cipher_context_t *ctx, const mbedtls_cipher_info_t *cipher_info )
{
    if( NULL == cipher_info || NULL == ctx )
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );

    memset( ctx, 0, sizeof( mbedtls_cipher_context_t ) );

    if( NULL == ( ctx->cipher_ctx = cipher_info->base->ctx_alloc_func() ) )
        return( MBEDTLS_ERR_CIPHER_ALLOC_FAILED );

    ctx->cipher_info = cipher_info;

#if defined(MBEDTLS_CIPHER_MODE_WITH_PADDING)
    /*
     * Ignore possible errors caused by a cipher mode that doesn't use padding
     */
#if defined(MBEDTLS_CIPHER_PADDING_PKCS7)
    (void) mbedtls_cipher_set_padding_mode( ctx, MBEDTLS_PADDING_PKCS7 );
#else
    (void) mbedtls_cipher_set_padding_mode( ctx, MBEDTLS_PADDING_NONE );
#endif
#endif /* MBEDTLS_CIPHER_MODE_WITH_PADDING */

    return( 0 );
}