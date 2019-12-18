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
struct TYPE_3__ {unsigned char tag; unsigned char* p; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ mbedtls_asn1_buf ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 unsigned char MBEDTLS_ASN1_OID ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int MBEDTLS_ERR_PK_KEY_INVALID_FORMAT ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pk_get_ecparams( unsigned char **p, const unsigned char *end,
                            mbedtls_asn1_buf *params )
{
    int ret;

    /* Tag may be either OID or SEQUENCE */
    params->tag = **p;
    if( params->tag != MBEDTLS_ASN1_OID
#if defined(MBEDTLS_PK_PARSE_EC_EXTENDED)
            && params->tag != ( MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE )
#endif
            )
    {
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );
    }

    if( ( ret = mbedtls_asn1_get_tag( p, end, &params->len, params->tag ) ) != 0 )
    {
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );
    }

    params->p = *p;
    *p += params->len;

    if( *p != end )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}