#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  N; int /*<<< orphan*/  len; int /*<<< orphan*/  E; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_PK_INVALID_PUBKEY ; 
 int mbedtls_asn1_get_mpi (unsigned char**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_size (int /*<<< orphan*/ *) ; 
 int mbedtls_rsa_check_pubkey (TYPE_1__*) ; 

__attribute__((used)) static int pk_get_rsapubkey( unsigned char **p,
                             const unsigned char *end,
                             mbedtls_rsa_context *rsa )
{
    int ret;
    size_t len;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( MBEDTLS_ERR_PK_INVALID_PUBKEY + ret );

    if( *p + len != end )
        return( MBEDTLS_ERR_PK_INVALID_PUBKEY +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    if( ( ret = mbedtls_asn1_get_mpi( p, end, &rsa->N ) ) != 0 ||
        ( ret = mbedtls_asn1_get_mpi( p, end, &rsa->E ) ) != 0 )
        return( MBEDTLS_ERR_PK_INVALID_PUBKEY + ret );

    if( *p != end )
        return( MBEDTLS_ERR_PK_INVALID_PUBKEY +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    if( ( ret = mbedtls_rsa_check_pubkey( rsa ) ) != 0 )
        return( MBEDTLS_ERR_PK_INVALID_PUBKEY );

    rsa->len = mbedtls_mpi_size( &rsa->N );

    return( 0 );
}