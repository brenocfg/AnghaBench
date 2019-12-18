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
typedef  int /*<<< orphan*/  mbedtls_gcm_context ;
struct TYPE_5__ {scalar_t__ operation; scalar_t__ cipher_ctx; TYPE_1__* cipher_info; } ;
typedef  TYPE_2__ mbedtls_cipher_context_t ;
struct TYPE_4__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ MBEDTLS_ENCRYPT ; 
 int MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA ; 
 scalar_t__ MBEDTLS_MODE_GCM ; 
 int mbedtls_gcm_finish (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

int mbedtls_cipher_write_tag( mbedtls_cipher_context_t *ctx,
                      unsigned char *tag, size_t tag_len )
{
    if( NULL == ctx || NULL == ctx->cipher_info || NULL == tag )
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );

    if( MBEDTLS_ENCRYPT != ctx->operation )
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );

    if( MBEDTLS_MODE_GCM == ctx->cipher_info->mode )
        return mbedtls_gcm_finish( (mbedtls_gcm_context *) ctx->cipher_ctx, tag, tag_len );

    return( 0 );
}