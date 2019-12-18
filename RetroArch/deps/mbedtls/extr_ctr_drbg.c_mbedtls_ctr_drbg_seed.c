#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_ctr_drbg_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_CTR_DRBG_ENTROPY_LEN ; 
 int mbedtls_ctr_drbg_seed_entropy_len (int /*<<< orphan*/ *,int (*) (void*,unsigned char*,size_t),void*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

int mbedtls_ctr_drbg_seed( mbedtls_ctr_drbg_context *ctx,
                   int (*f_entropy)(void *, unsigned char *, size_t),
                   void *p_entropy,
                   const unsigned char *custom,
                   size_t len )
{
    return( mbedtls_ctr_drbg_seed_entropy_len( ctx, f_entropy, p_entropy, custom, len,
                                       MBEDTLS_CTR_DRBG_ENTROPY_LEN ) );
}