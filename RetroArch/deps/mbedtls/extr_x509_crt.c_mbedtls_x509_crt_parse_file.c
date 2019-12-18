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
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (unsigned char*) ; 
 int mbedtls_pk_load_file (char const*,unsigned char**,size_t*) ; 
 int mbedtls_x509_crt_parse (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,size_t) ; 

int mbedtls_x509_crt_parse_file( mbedtls_x509_crt *chain, const char *path )
{
    int ret;
    size_t n;
    unsigned char *buf;

    if( ( ret = mbedtls_pk_load_file( path, &buf, &n ) ) != 0 )
        return( ret );

    ret = mbedtls_x509_crt_parse( chain, buf, n );

    mbedtls_zeroize( buf, n );
    mbedtls_free( buf );

    return( ret );
}