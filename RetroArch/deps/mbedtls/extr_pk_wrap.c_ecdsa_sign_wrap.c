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
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_ecdsa_context ;

/* Variables and functions */
 int mbedtls_ecdsa_write_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,size_t*,int (*) (void*,unsigned char*,size_t),void*) ; 

__attribute__((used)) static int ecdsa_sign_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    return( mbedtls_ecdsa_write_signature( (mbedtls_ecdsa_context *) ctx,
                md_alg, hash, hash_len, sig, sig_len, f_rng, p_rng ) );
}