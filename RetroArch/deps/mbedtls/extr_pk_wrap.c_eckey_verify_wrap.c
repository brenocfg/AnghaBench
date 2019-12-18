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
 int ecdsa_verify_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_ecdsa_free (int /*<<< orphan*/ *) ; 
 int mbedtls_ecdsa_from_keypair (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mbedtls_ecdsa_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eckey_verify_wrap( void *ctx, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len )
{
    int ret;
    mbedtls_ecdsa_context ecdsa;

    mbedtls_ecdsa_init( &ecdsa );

    if( ( ret = mbedtls_ecdsa_from_keypair( &ecdsa, ctx ) ) == 0 )
        ret = ecdsa_verify_wrap( &ecdsa, md_alg, hash, hash_len, sig, sig_len );

    mbedtls_ecdsa_free( &ecdsa );

    return( ret );
}