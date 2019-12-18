#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ padding; size_t len; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;

/* Variables and functions */
 int MBEDTLS_ERR_RSA_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_RSA_RNG_FAILED ; 
 int /*<<< orphan*/  MBEDTLS_RSA_CRYPT ; 
 scalar_t__ MBEDTLS_RSA_PKCS_V15 ; 
 int MBEDTLS_RSA_PRIVATE ; 
 int MBEDTLS_RSA_PUBLIC ; 
 int /*<<< orphan*/  MBEDTLS_RSA_SIGN ; 
 int mbedtls_rsa_private (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*,unsigned char*,unsigned char*) ; 
 int mbedtls_rsa_public (TYPE_1__*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 

int mbedtls_rsa_rsaes_pkcs1_v15_encrypt( mbedtls_rsa_context *ctx,
                                 int (*f_rng)(void *, unsigned char *, size_t),
                                 void *p_rng,
                                 int mode, size_t ilen,
                                 const unsigned char *input,
                                 unsigned char *output )
{
    size_t nb_pad, olen;
    int ret;
    unsigned char *p = output;

    if( mode == MBEDTLS_RSA_PRIVATE && ctx->padding != MBEDTLS_RSA_PKCS_V15 )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    /* We don't check p_rng because it won't be dereferenced here */
    if( f_rng == NULL || input == NULL || output == NULL )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    olen = ctx->len;

    /* first comparison checks for overflow */
    if( ilen + 11 < ilen || olen < ilen + 11 )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    nb_pad = olen - 3 - ilen;

    *p++ = 0;
    if( mode == MBEDTLS_RSA_PUBLIC )
    {
        *p++ = MBEDTLS_RSA_CRYPT;

        while( nb_pad-- > 0 )
        {
            int rng_dl = 100;

            do {
                ret = f_rng( p_rng, p, 1 );
            } while( *p == 0 && --rng_dl && ret == 0 );

            /* Check if RNG failed to generate data */
            if( rng_dl == 0 || ret != 0 )
                return( MBEDTLS_ERR_RSA_RNG_FAILED + ret );

            p++;
        }
    }
    else
    {
        *p++ = MBEDTLS_RSA_SIGN;

        while( nb_pad-- > 0 )
            *p++ = 0xFF;
    }

    *p++ = 0;
    memcpy( p, input, ilen );

    return( ( mode == MBEDTLS_RSA_PUBLIC )
            ? mbedtls_rsa_public(  ctx, output, output )
            : mbedtls_rsa_private( ctx, f_rng, p_rng, output, output ) );
}