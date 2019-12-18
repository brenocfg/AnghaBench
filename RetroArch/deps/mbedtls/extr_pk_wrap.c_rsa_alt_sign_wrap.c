#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t (* key_len_func ) (int /*<<< orphan*/ ) ;int (* sign_func ) (int /*<<< orphan*/ ,int (*) (void*,unsigned char*,size_t),void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned char const*,unsigned char*) ;int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ mbedtls_rsa_alt_context ;
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;

/* Variables and functions */
 int MBEDTLS_ERR_PK_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_RSA_PRIVATE ; 
 size_t UINT_MAX ; 
 size_t stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int (*) (void*,unsigned char*,size_t),void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned char const*,unsigned char*) ; 

__attribute__((used)) static int rsa_alt_sign_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    mbedtls_rsa_alt_context *rsa_alt = (mbedtls_rsa_alt_context *) ctx;

#if defined(MBEDTLS_HAVE_INT64)
    if( UINT_MAX < hash_len )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );
#endif /* MBEDTLS_HAVE_INT64 */

    *sig_len = rsa_alt->key_len_func( rsa_alt->key );

    return( rsa_alt->sign_func( rsa_alt->key, f_rng, p_rng, MBEDTLS_RSA_PRIVATE,
                md_alg, (unsigned int) hash_len, hash, sig ) );
}