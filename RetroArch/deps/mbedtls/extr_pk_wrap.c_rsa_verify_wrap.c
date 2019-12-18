#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t len; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;
typedef  scalar_t__ mbedtls_md_type_t ;

/* Variables and functions */
 int MBEDTLS_ERR_PK_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_PK_SIG_LEN_MISMATCH ; 
 int MBEDTLS_ERR_RSA_VERIFY_FAILED ; 
 scalar_t__ MBEDTLS_MD_NONE ; 
 int /*<<< orphan*/  MBEDTLS_RSA_PUBLIC ; 
 size_t UINT_MAX ; 
 int mbedtls_rsa_pkcs1_verify (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned char const*,unsigned char const*) ; 

__attribute__((used)) static int rsa_verify_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   const unsigned char *sig, size_t sig_len )
{
    int ret;

#if defined(MBEDTLS_HAVE_INT64)
    if( md_alg == MBEDTLS_MD_NONE && UINT_MAX < hash_len )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );
#endif /* MBEDTLS_HAVE_INT64 */

    if( sig_len < ((mbedtls_rsa_context *) ctx)->len )
        return( MBEDTLS_ERR_RSA_VERIFY_FAILED );

    if( ( ret = mbedtls_rsa_pkcs1_verify( (mbedtls_rsa_context *) ctx, NULL, NULL,
                                  MBEDTLS_RSA_PUBLIC, md_alg,
                                  (unsigned int) hash_len, hash, sig ) ) != 0 )
        return( ret );

    if( sig_len > ((mbedtls_rsa_context *) ctx)->len )
        return( MBEDTLS_ERR_PK_SIG_LEN_MISMATCH );

    return( 0 );
}