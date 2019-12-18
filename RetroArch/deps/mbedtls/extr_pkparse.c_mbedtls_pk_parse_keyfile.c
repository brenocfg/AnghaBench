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
typedef  int /*<<< orphan*/  mbedtls_pk_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (unsigned char*) ; 
 int mbedtls_pk_load_file (char const*,unsigned char**,size_t*) ; 
 int mbedtls_pk_parse_key (int /*<<< orphan*/ *,unsigned char*,size_t,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,size_t) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int mbedtls_pk_parse_keyfile( mbedtls_pk_context *ctx,
                      const char *path, const char *pwd )
{
    int ret;
    size_t n;
    unsigned char *buf;

    if( ( ret = mbedtls_pk_load_file( path, &buf, &n ) ) != 0 )
        return( ret );

    if( pwd == NULL )
        ret = mbedtls_pk_parse_key( ctx, buf, n, NULL, 0 );
    else
        ret = mbedtls_pk_parse_key( ctx, buf, n,
                (const unsigned char *) pwd, strlen( pwd ) );

    mbedtls_zeroize( buf, n );
    mbedtls_free( buf );

    return( ret );
}