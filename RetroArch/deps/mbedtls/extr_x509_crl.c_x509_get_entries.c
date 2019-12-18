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
struct TYPE_5__ {unsigned char tag; unsigned char* p; size_t len; } ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  entry_ext; int /*<<< orphan*/  revocation_date; int /*<<< orphan*/  serial; TYPE_1__ raw; } ;
typedef  TYPE_2__ mbedtls_x509_crl_entry ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int MBEDTLS_ERR_X509_ALLOC_FAILED ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int) ; 
 TYPE_2__* mbedtls_calloc (int,int) ; 
 int mbedtls_x509_get_serial (unsigned char**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int mbedtls_x509_get_time (unsigned char**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int x509_get_crl_entry_ext (unsigned char**,unsigned char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int x509_get_entries( unsigned char **p,
                             const unsigned char *end,
                             mbedtls_x509_crl_entry *entry )
{
    int ret;
    size_t entry_len;
    mbedtls_x509_crl_entry *cur_entry = entry;

    if( *p == end )
        return( 0 );

    if( ( ret = mbedtls_asn1_get_tag( p, end, &entry_len,
            MBEDTLS_ASN1_SEQUENCE | MBEDTLS_ASN1_CONSTRUCTED ) ) != 0 )
    {
        if( ret == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
            return( 0 );

        return( ret );
    }

    end = *p + entry_len;

    while( *p < end )
    {
        size_t len2;
        const unsigned char *end2;

        if( ( ret = mbedtls_asn1_get_tag( p, end, &len2,
                MBEDTLS_ASN1_SEQUENCE | MBEDTLS_ASN1_CONSTRUCTED ) ) != 0 )
        {
            return( ret );
        }

        cur_entry->raw.tag = **p;
        cur_entry->raw.p = *p;
        cur_entry->raw.len = len2;
        end2 = *p + len2;

        if( ( ret = mbedtls_x509_get_serial( p, end2, &cur_entry->serial ) ) != 0 )
            return( ret );

        if( ( ret = mbedtls_x509_get_time( p, end2,
                                   &cur_entry->revocation_date ) ) != 0 )
            return( ret );

        if( ( ret = x509_get_crl_entry_ext( p, end2,
                                            &cur_entry->entry_ext ) ) != 0 )
            return( ret );

        if( *p < end )
        {
            cur_entry->next = mbedtls_calloc( 1, sizeof( mbedtls_x509_crl_entry ) );

            if( cur_entry->next == NULL )
                return( MBEDTLS_ERR_X509_ALLOC_FAILED );

            cur_entry = cur_entry->next;
        }
    }

    return( 0 );
}