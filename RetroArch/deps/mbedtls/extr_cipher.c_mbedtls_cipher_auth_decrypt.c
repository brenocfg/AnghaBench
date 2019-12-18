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
struct TYPE_5__ {int /*<<< orphan*/  cipher_ctx; TYPE_1__* cipher_info; } ;
typedef  TYPE_2__ mbedtls_cipher_context_t ;
struct TYPE_4__ {scalar_t__ mode; } ;

/* Variables and functions */
 int MBEDTLS_ERR_CCM_AUTH_FAILED ; 
 int MBEDTLS_ERR_CIPHER_AUTH_FAILED ; 
 int MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_GCM_AUTH_FAILED ; 
 scalar_t__ MBEDTLS_MODE_CCM ; 
 scalar_t__ MBEDTLS_MODE_GCM ; 
 int mbedtls_ccm_auth_decrypt (int /*<<< orphan*/ ,size_t,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,unsigned char*,unsigned char const*,size_t) ; 
 int mbedtls_gcm_auth_decrypt (int /*<<< orphan*/ ,size_t,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,unsigned char*) ; 

int mbedtls_cipher_auth_decrypt( mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         const unsigned char *tag, size_t tag_len )
{
#if defined(MBEDTLS_GCM_C)
    if( MBEDTLS_MODE_GCM == ctx->cipher_info->mode )
    {
        int ret;

        *olen = ilen;
        ret = mbedtls_gcm_auth_decrypt( ctx->cipher_ctx, ilen,
                                iv, iv_len, ad, ad_len,
                                tag, tag_len, input, output );

        if( ret == MBEDTLS_ERR_GCM_AUTH_FAILED )
            ret = MBEDTLS_ERR_CIPHER_AUTH_FAILED;

        return( ret );
    }
#endif /* MBEDTLS_GCM_C */
#if defined(MBEDTLS_CCM_C)
    if( MBEDTLS_MODE_CCM == ctx->cipher_info->mode )
    {
        int ret;

        *olen = ilen;
        ret = mbedtls_ccm_auth_decrypt( ctx->cipher_ctx, ilen,
                                iv, iv_len, ad, ad_len,
                                input, output, tag, tag_len );

        if( ret == MBEDTLS_ERR_CCM_AUTH_FAILED )
            ret = MBEDTLS_ERR_CIPHER_AUTH_FAILED;

        return( ret );
    }
#endif /* MBEDTLS_CCM_C */

    return( MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE );
}