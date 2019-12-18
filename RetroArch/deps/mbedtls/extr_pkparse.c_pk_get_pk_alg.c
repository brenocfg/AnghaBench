#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mbedtls_pk_type_t ;
struct TYPE_7__ {scalar_t__ tag; scalar_t__ len; } ;
typedef  TYPE_1__ mbedtls_asn1_buf ;

/* Variables and functions */
 scalar_t__ MBEDTLS_ASN1_NULL ; 
 int MBEDTLS_ERR_PK_INVALID_ALG ; 
 int MBEDTLS_ERR_PK_UNKNOWN_PK_ALG ; 
 scalar_t__ MBEDTLS_PK_RSA ; 
 int mbedtls_asn1_get_alg (unsigned char**,unsigned char const*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ mbedtls_oid_get_pk_alg (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pk_get_pk_alg( unsigned char **p,
                          const unsigned char *end,
                          mbedtls_pk_type_t *pk_alg, mbedtls_asn1_buf *params )
{
    int ret;
    mbedtls_asn1_buf alg_oid;

    memset( params, 0, sizeof(mbedtls_asn1_buf) );

    if( ( ret = mbedtls_asn1_get_alg( p, end, &alg_oid, params ) ) != 0 )
        return( MBEDTLS_ERR_PK_INVALID_ALG + ret );

    if( mbedtls_oid_get_pk_alg( &alg_oid, pk_alg ) != 0 )
        return( MBEDTLS_ERR_PK_UNKNOWN_PK_ALG );

    /*
     * No parameters with RSA (only for EC)
     */
    if( *pk_alg == MBEDTLS_PK_RSA &&
            ( ( params->tag != MBEDTLS_ASN1_NULL && params->tag != 0 ) ||
                params->len != 0 ) )
    {
        return( MBEDTLS_ERR_PK_INVALID_ALG );
    }

    return( 0 );
}