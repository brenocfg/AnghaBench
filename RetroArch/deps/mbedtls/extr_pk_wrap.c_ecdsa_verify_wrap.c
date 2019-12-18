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
typedef  scalar_t__ mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_ecdsa_context ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_SIG_LEN_MISMATCH ; 
 int MBEDTLS_ERR_PK_SIG_LEN_MISMATCH ; 
 int mbedtls_ecdsa_read_signature (int /*<<< orphan*/ *,unsigned char const*,size_t,unsigned char const*,size_t) ; 

__attribute__((used)) static int ecdsa_verify_wrap( void *ctx, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len )
{
    int ret;
    ((void) md_alg);

    ret = mbedtls_ecdsa_read_signature( (mbedtls_ecdsa_context *) ctx,
                                hash, hash_len, sig, sig_len );

    if( ret == MBEDTLS_ERR_ECP_SIG_LEN_MISMATCH )
        return( MBEDTLS_ERR_PK_SIG_LEN_MISMATCH );

    return( ret );
}