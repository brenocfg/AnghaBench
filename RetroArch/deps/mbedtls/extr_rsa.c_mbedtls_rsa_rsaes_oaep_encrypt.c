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
struct TYPE_5__ {scalar_t__ padding; size_t len; scalar_t__ hash_id; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_md_info_t ;
typedef  int /*<<< orphan*/  mbedtls_md_context_t ;

/* Variables and functions */
 int MBEDTLS_ERR_RSA_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_RSA_RNG_FAILED ; 
 scalar_t__ MBEDTLS_RSA_PKCS_V21 ; 
 int MBEDTLS_RSA_PRIVATE ; 
 int MBEDTLS_RSA_PUBLIC ; 
 int /*<<< orphan*/  mbedtls_md (int /*<<< orphan*/  const*,unsigned char const*,size_t,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md_free (int /*<<< orphan*/ *) ; 
 unsigned int mbedtls_md_get_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * mbedtls_md_info_from_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_md_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md_setup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int mbedtls_rsa_private (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*,unsigned char*,unsigned char*) ; 
 int mbedtls_rsa_public (TYPE_1__*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mgf_mask (unsigned char*,unsigned int,unsigned char*,size_t,int /*<<< orphan*/ *) ; 

int mbedtls_rsa_rsaes_oaep_encrypt( mbedtls_rsa_context *ctx,
                            int (*f_rng)(void *, unsigned char *, size_t),
                            void *p_rng,
                            int mode,
                            const unsigned char *label, size_t label_len,
                            size_t ilen,
                            const unsigned char *input,
                            unsigned char *output )
{
    size_t olen;
    int ret;
    unsigned char *p = output;
    unsigned int hlen;
    const mbedtls_md_info_t *md_info;
    mbedtls_md_context_t md_ctx;

    if( mode == MBEDTLS_RSA_PRIVATE && ctx->padding != MBEDTLS_RSA_PKCS_V21 )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    if( f_rng == NULL )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    md_info = mbedtls_md_info_from_type( (mbedtls_md_type_t) ctx->hash_id );
    if( md_info == NULL )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    olen = ctx->len;
    hlen = mbedtls_md_get_size( md_info );

    /* first comparison checks for overflow */
    if( ilen + 2 * hlen + 2 < ilen || olen < ilen + 2 * hlen + 2 )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    memset( output, 0, olen );

    *p++ = 0;

    /* Generate a random octet string seed */
    if( ( ret = f_rng( p_rng, p, hlen ) ) != 0 )
        return( MBEDTLS_ERR_RSA_RNG_FAILED + ret );

    p += hlen;

    /* Construct DB */
    mbedtls_md( md_info, label, label_len, p );
    p += hlen;
    p += olen - 2 * hlen - 2 - ilen;
    *p++ = 1;
    memcpy( p, input, ilen );

    mbedtls_md_init( &md_ctx );
    if( ( ret = mbedtls_md_setup( &md_ctx, md_info, 0 ) ) != 0 )
    {
        mbedtls_md_free( &md_ctx );
        return( ret );
    }

    /* maskedDB: Apply dbMask to DB */
    mgf_mask( output + hlen + 1, olen - hlen - 1, output + 1, hlen,
               &md_ctx );

    /* maskedSeed: Apply seedMask to seed */
    mgf_mask( output + 1, hlen, output + hlen + 1, olen - hlen - 1,
               &md_ctx );

    mbedtls_md_free( &md_ctx );

    return( ( mode == MBEDTLS_RSA_PUBLIC )
            ? mbedtls_rsa_public(  ctx, output, output )
            : mbedtls_rsa_private( ctx, f_rng, p_rng, output, output ) );
}