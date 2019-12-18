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
typedef  int /*<<< orphan*/  salt ;
struct TYPE_5__ {scalar_t__ padding; size_t len; int /*<<< orphan*/  N; scalar_t__ hash_id; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;
typedef  scalar_t__ mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_md_info_t ;
typedef  int /*<<< orphan*/  mbedtls_md_context_t ;

/* Variables and functions */
 int MBEDTLS_ERR_RSA_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_RSA_RNG_FAILED ; 
 int MBEDTLS_MD_MAX_SIZE ; 
 scalar_t__ MBEDTLS_MD_NONE ; 
 scalar_t__ MBEDTLS_RSA_PKCS_V21 ; 
 int MBEDTLS_RSA_PRIVATE ; 
 int MBEDTLS_RSA_PUBLIC ; 
 int /*<<< orphan*/  mbedtls_md_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md_free (int /*<<< orphan*/ *) ; 
 unsigned int mbedtls_md_get_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * mbedtls_md_info_from_type (scalar_t__) ; 
 int /*<<< orphan*/  mbedtls_md_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md_setup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_md_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md_update (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int mbedtls_mpi_bitlen (int /*<<< orphan*/ *) ; 
 int mbedtls_rsa_private (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*,unsigned char*,unsigned char*) ; 
 int mbedtls_rsa_public (TYPE_1__*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mgf_mask (unsigned char*,size_t,unsigned char*,unsigned int,int /*<<< orphan*/ *) ; 

int mbedtls_rsa_rsassa_pss_sign( mbedtls_rsa_context *ctx,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng,
                         int mode,
                         mbedtls_md_type_t md_alg,
                         unsigned int hashlen,
                         const unsigned char *hash,
                         unsigned char *sig )
{
    size_t olen;
    unsigned char *p = sig;
    unsigned char salt[MBEDTLS_MD_MAX_SIZE];
    unsigned int slen, hlen, offset = 0;
    int ret;
    size_t msb;
    const mbedtls_md_info_t *md_info;
    mbedtls_md_context_t md_ctx;

    if( mode == MBEDTLS_RSA_PRIVATE && ctx->padding != MBEDTLS_RSA_PKCS_V21 )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    if( f_rng == NULL )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    olen = ctx->len;

    if( md_alg != MBEDTLS_MD_NONE )
    {
        /* Gather length of hash to sign */
        md_info = mbedtls_md_info_from_type( md_alg );
        if( md_info == NULL )
            return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

        hashlen = mbedtls_md_get_size( md_info );
    }

    md_info = mbedtls_md_info_from_type( (mbedtls_md_type_t) ctx->hash_id );
    if( md_info == NULL )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    hlen = mbedtls_md_get_size( md_info );
    slen = hlen;

    if( olen < hlen + slen + 2 )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    memset( sig, 0, olen );

    /* Generate salt of length slen */
    if( ( ret = f_rng( p_rng, salt, slen ) ) != 0 )
        return( MBEDTLS_ERR_RSA_RNG_FAILED + ret );

    /* Note: EMSA-PSS encoding is over the length of N - 1 bits */
    msb = mbedtls_mpi_bitlen( &ctx->N ) - 1;
    p += olen - hlen * 2 - 2;
    *p++ = 0x01;
    memcpy( p, salt, slen );
    p += slen;

    mbedtls_md_init( &md_ctx );
    if( ( ret = mbedtls_md_setup( &md_ctx, md_info, 0 ) ) != 0 )
    {
        mbedtls_md_free( &md_ctx );
        /* No need to zeroize salt: we didn't use it. */
        return( ret );
    }

    /* Generate H = Hash( M' ) */
    mbedtls_md_starts( &md_ctx );
    mbedtls_md_update( &md_ctx, p, 8 );
    mbedtls_md_update( &md_ctx, hash, hashlen );
    mbedtls_md_update( &md_ctx, salt, slen );
    mbedtls_md_finish( &md_ctx, p );
    mbedtls_zeroize( salt, sizeof( salt ) );

    /* Compensate for boundary condition when applying mask */
    if( msb % 8 == 0 )
        offset = 1;

    /* maskedDB: Apply dbMask to DB */
    mgf_mask( sig + offset, olen - hlen - 1 - offset, p, hlen, &md_ctx );

    mbedtls_md_free( &md_ctx );

    msb = mbedtls_mpi_bitlen( &ctx->N ) - 1;
    sig[0] &= 0xFF >> ( olen * 8 - msb );

    p += hlen;
    *p++ = 0xBC;

    return( ( mode == MBEDTLS_RSA_PUBLIC )
            ? mbedtls_rsa_public(  ctx, sig, sig )
            : mbedtls_rsa_private( ctx, f_rng, p_rng, sig, sig ) );
}