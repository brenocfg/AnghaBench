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
struct TYPE_4__ {int (* f_entropy ) (void*,unsigned char*,size_t) ;size_t entropy_len; int /*<<< orphan*/  aes_ctx; int /*<<< orphan*/  reseed_interval; void* p_entropy; } ;
typedef  TYPE_1__ mbedtls_ctr_drbg_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_CTR_DRBG_KEYBITS ; 
 int MBEDTLS_CTR_DRBG_KEYSIZE ; 
 int /*<<< orphan*/  MBEDTLS_CTR_DRBG_RESEED_INTERVAL ; 
 int /*<<< orphan*/  mbedtls_aes_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_aes_setkey_enc (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int mbedtls_ctr_drbg_reseed (TYPE_1__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

int mbedtls_ctr_drbg_seed_entropy_len(
                   mbedtls_ctr_drbg_context *ctx,
                   int (*f_entropy)(void *, unsigned char *, size_t),
                   void *p_entropy,
                   const unsigned char *custom,
                   size_t len,
                   size_t entropy_len )
{
    int ret;
    unsigned char key[MBEDTLS_CTR_DRBG_KEYSIZE];

    memset( key, 0, MBEDTLS_CTR_DRBG_KEYSIZE );

    mbedtls_aes_init( &ctx->aes_ctx );

    ctx->f_entropy = f_entropy;
    ctx->p_entropy = p_entropy;

    ctx->entropy_len = entropy_len;
    ctx->reseed_interval = MBEDTLS_CTR_DRBG_RESEED_INTERVAL;

    /*
     * Initialize with an empty key
     */
    mbedtls_aes_setkey_enc( &ctx->aes_ctx, key, MBEDTLS_CTR_DRBG_KEYBITS );

    if( ( ret = mbedtls_ctr_drbg_reseed( ctx, custom, len ) ) != 0 )
        return( ret );

    return( 0 );
}