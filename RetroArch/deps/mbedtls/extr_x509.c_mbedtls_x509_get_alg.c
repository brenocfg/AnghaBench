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
typedef  int /*<<< orphan*/  mbedtls_x509_buf ;

/* Variables and functions */
 int MBEDTLS_ERR_X509_INVALID_ALG ; 
 int mbedtls_asn1_get_alg (unsigned char**,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mbedtls_x509_get_alg( unsigned char **p, const unsigned char *end,
                  mbedtls_x509_buf *alg, mbedtls_x509_buf *params )
{
    int ret;

    if( ( ret = mbedtls_asn1_get_alg( p, end, alg, params ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_ALG + ret );

    return( 0 );
}