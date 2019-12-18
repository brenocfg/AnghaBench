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
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int MBEDTLS_ERR_RSA_KEY_CHECK_FAILED ; 
 int /*<<< orphan*/  MBEDTLS_MD_NONE ; 
 int MBEDTLS_MPI_MAX_SIZE ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 scalar_t__ rsa_alt_get_bitlen (void const*) ; 
 int rsa_alt_sign_wrap (void*,int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rsa_get_bitlen (void const*) ; 
 scalar_t__ rsa_verify_wrap (void*,int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,size_t) ; 

__attribute__((used)) static int rsa_alt_check_pair( const void *pub, const void *prv )
{
    unsigned char sig[MBEDTLS_MPI_MAX_SIZE];
    unsigned char hash[32];
    size_t sig_len = 0;
    int ret;

    if( rsa_alt_get_bitlen( prv ) != rsa_get_bitlen( pub ) )
        return( MBEDTLS_ERR_RSA_KEY_CHECK_FAILED );

    memset( hash, 0x2a, sizeof( hash ) );

    if( ( ret = rsa_alt_sign_wrap( (void *) prv, MBEDTLS_MD_NONE,
                                   hash, sizeof( hash ),
                                   sig, &sig_len, NULL, NULL ) ) != 0 )
    {
        return( ret );
    }

    if( rsa_verify_wrap( (void *) pub, MBEDTLS_MD_NONE,
                         hash, sizeof( hash ), sig, sig_len ) != 0 )
    {
        return( MBEDTLS_ERR_RSA_KEY_CHECK_FAILED );
    }

    return( 0 );
}