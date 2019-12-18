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
struct TYPE_4__ {size_t entropy_len; scalar_t__ (* f_entropy ) (int /*<<< orphan*/ ,unsigned char*,size_t) ;int reseed_counter; int /*<<< orphan*/  p_entropy; } ;
typedef  TYPE_1__ mbedtls_hmac_drbg_context ;

/* Variables and functions */
 int MBEDTLS_ERR_HMAC_DRBG_ENTROPY_SOURCE_FAILED ; 
 int MBEDTLS_ERR_HMAC_DRBG_INPUT_TOO_BIG ; 
 size_t MBEDTLS_HMAC_DRBG_MAX_INPUT ; 
 int MBEDTLS_HMAC_DRBG_MAX_SEED_INPUT ; 
 int /*<<< orphan*/  mbedtls_hmac_drbg_update (TYPE_1__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

int mbedtls_hmac_drbg_reseed( mbedtls_hmac_drbg_context *ctx,
                      const unsigned char *additional, size_t len )
{
    unsigned char seed[MBEDTLS_HMAC_DRBG_MAX_SEED_INPUT];
    size_t seedlen;

    /* III. Check input length */
    if( len > MBEDTLS_HMAC_DRBG_MAX_INPUT ||
        ctx->entropy_len + len > MBEDTLS_HMAC_DRBG_MAX_SEED_INPUT )
    {
        return( MBEDTLS_ERR_HMAC_DRBG_INPUT_TOO_BIG );
    }

    memset( seed, 0, MBEDTLS_HMAC_DRBG_MAX_SEED_INPUT );

    /* IV. Gather entropy_len bytes of entropy for the seed */
    if( ctx->f_entropy( ctx->p_entropy, seed, ctx->entropy_len ) != 0 )
        return( MBEDTLS_ERR_HMAC_DRBG_ENTROPY_SOURCE_FAILED );

    seedlen = ctx->entropy_len;

    /* 1. Concatenate entropy and additional data if any */
    if( additional != NULL && len != 0 )
    {
        memcpy( seed + seedlen, additional, len );
        seedlen += len;
    }

    /* 2. Update state */
    mbedtls_hmac_drbg_update( ctx, seed, seedlen );

    /* 3. Reset reseed_counter */
    ctx->reseed_counter = 1;

    /* 4. Done */
    return( 0 );
}