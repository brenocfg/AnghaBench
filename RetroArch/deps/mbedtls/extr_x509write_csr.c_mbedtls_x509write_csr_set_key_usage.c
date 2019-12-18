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
typedef  int /*<<< orphan*/  mbedtls_x509write_csr ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_OID_KEY_USAGE ; 
 int /*<<< orphan*/  MBEDTLS_OID_SIZE (int /*<<< orphan*/ ) ; 
 int mbedtls_asn1_write_bitstring (unsigned char**,unsigned char*,unsigned char*,int) ; 
 int mbedtls_x509write_csr_set_extension (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

int mbedtls_x509write_csr_set_key_usage( mbedtls_x509write_csr *ctx, unsigned char key_usage )
{
    unsigned char buf[4];
    unsigned char *c;
    int ret;

    c = buf + 4;

    if( ( ret = mbedtls_asn1_write_bitstring( &c, buf, &key_usage, 7 ) ) != 4 )
        return( ret );

    ret = mbedtls_x509write_csr_set_extension( ctx, MBEDTLS_OID_KEY_USAGE,
                                       MBEDTLS_OID_SIZE( MBEDTLS_OID_KEY_USAGE ),
                                       buf, 4 );
    if( ret != 0 )
        return( ret );

    return( 0 );
}