#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p; } ;
struct TYPE_6__ {TYPE_1__ buf; } ;
typedef  TYPE_2__ mbedtls_x509_sequence ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ASN1_OID ; 
 int MBEDTLS_ERR_ASN1_INVALID_LENGTH ; 
 int MBEDTLS_ERR_X509_INVALID_EXTENSIONS ; 
 int mbedtls_asn1_get_sequence_of (unsigned char**,unsigned char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x509_get_ext_key_usage( unsigned char **p,
                               const unsigned char *end,
                               mbedtls_x509_sequence *ext_key_usage)
{
    int ret;

    if( ( ret = mbedtls_asn1_get_sequence_of( p, end, ext_key_usage, MBEDTLS_ASN1_OID ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

    /* Sequence length must be >= 1 */
    if( ext_key_usage->buf.p == NULL )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_INVALID_LENGTH );

    return( 0 );
}