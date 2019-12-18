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
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE ; 
 scalar_t__ MBEDTLS_PK_ECKEY ; 
 scalar_t__ MBEDTLS_PK_RSA ; 
 int /*<<< orphan*/  mbedtls_pk_ec (int /*<<< orphan*/  const) ; 
 scalar_t__ mbedtls_pk_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_pk_rsa (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pk_write_ec_pubkey (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pk_write_rsa_pubkey (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 

int mbedtls_pk_write_pubkey( unsigned char **p, unsigned char *start,
                     const mbedtls_pk_context *key )
{
    int ret;
    size_t len = 0;

#if defined(MBEDTLS_RSA_C)
    if( mbedtls_pk_get_type( key ) == MBEDTLS_PK_RSA )
        MBEDTLS_ASN1_CHK_ADD( len, pk_write_rsa_pubkey( p, start, mbedtls_pk_rsa( *key ) ) );
    else
#endif
#if defined(MBEDTLS_ECP_C)
    if( mbedtls_pk_get_type( key ) == MBEDTLS_PK_ECKEY )
        MBEDTLS_ASN1_CHK_ADD( len, pk_write_ec_pubkey( p, start, mbedtls_pk_ec( *key ) ) );
    else
#endif
        return( MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE );

    return( (int) len );
}