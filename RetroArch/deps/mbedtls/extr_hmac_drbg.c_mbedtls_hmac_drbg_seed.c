#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_md_info_t ;
struct TYPE_4__ {int (* f_entropy ) (void*,unsigned char*,size_t) ;size_t entropy_len; int /*<<< orphan*/  reseed_interval; void* p_entropy; int /*<<< orphan*/  V; int /*<<< orphan*/  md_ctx; } ;
typedef  TYPE_1__ mbedtls_hmac_drbg_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_HMAC_DRBG_RESEED_INTERVAL ; 
 int mbedtls_hmac_drbg_reseed (TYPE_1__*,unsigned char const*,size_t) ; 
 size_t mbedtls_md_get_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_md_hmac_starts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int mbedtls_md_setup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,size_t) ; 

int mbedtls_hmac_drbg_seed( mbedtls_hmac_drbg_context *ctx,
                    const mbedtls_md_info_t * md_info,
                    int (*f_entropy)(void *, unsigned char *, size_t),
                    void *p_entropy,
                    const unsigned char *custom,
                    size_t len )
{
    int ret;
    size_t entropy_len, md_size;

    if( ( ret = mbedtls_md_setup( &ctx->md_ctx, md_info, 1 ) ) != 0 )
        return( ret );

    md_size = mbedtls_md_get_size( md_info );

    /*
     * Set initial working state.
     * Use the V memory location, which is currently all 0, to initialize the
     * MD context with an all-zero key. Then set V to its initial value.
     */
    mbedtls_md_hmac_starts( &ctx->md_ctx, ctx->V, md_size );
    memset( ctx->V, 0x01, md_size );

    ctx->f_entropy = f_entropy;
    ctx->p_entropy = p_entropy;

    ctx->reseed_interval = MBEDTLS_HMAC_DRBG_RESEED_INTERVAL;

    /*
     * See SP800-57 5.6.1 (p. 65-66) for the security strength provided by
     * each hash function, then according to SP800-90A rev1 10.1 table 2,
     * min_entropy_len (in bits) is security_strength.
     *
     * (This also matches the sizes used in the NIST test vectors.)
     */
    entropy_len = md_size <= 20 ? 16 : /* 160-bits hash -> 128 bits */
                  md_size <= 28 ? 24 : /* 224-bits hash -> 192 bits */
                                  32;  /* better (256+) -> 256 bits */

    /*
     * For initialisation, use more entropy to emulate a nonce
     * (Again, matches test vectors.)
     */
    ctx->entropy_len = entropy_len * 3 / 2;

    if( ( ret = mbedtls_hmac_drbg_reseed( ctx, custom, len ) ) != 0 )
        return( ret );

    ctx->entropy_len = entropy_len;

    return( 0 );
}