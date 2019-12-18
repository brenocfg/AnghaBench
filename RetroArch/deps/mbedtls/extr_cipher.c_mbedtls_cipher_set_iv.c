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
struct TYPE_5__ {size_t iv_size; int /*<<< orphan*/  iv; TYPE_1__* cipher_info; } ;
typedef  TYPE_2__ mbedtls_cipher_context_t ;
struct TYPE_4__ {int flags; size_t iv_size; } ;

/* Variables and functions */
 int MBEDTLS_CIPHER_VARIABLE_IV_LEN ; 
 int MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE ; 
 size_t MBEDTLS_MAX_IV_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

int mbedtls_cipher_set_iv( mbedtls_cipher_context_t *ctx,
                   const unsigned char *iv, size_t iv_len )
{
    size_t actual_iv_size;

    if( NULL == ctx || NULL == ctx->cipher_info || NULL == iv )
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );

    /* avoid buffer overflow in ctx->iv */
    if( iv_len > MBEDTLS_MAX_IV_LENGTH )
        return( MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE );

    if( ( ctx->cipher_info->flags & MBEDTLS_CIPHER_VARIABLE_IV_LEN ) != 0 )
        actual_iv_size = iv_len;
    else
    {
        actual_iv_size = ctx->cipher_info->iv_size;

        /* avoid reading past the end of input buffer */
        if( actual_iv_size > iv_len )
            return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );
    }

    memcpy( ctx->iv, iv, actual_iv_size );
    ctx->iv_size = actual_iv_size;

    return( 0 );
}