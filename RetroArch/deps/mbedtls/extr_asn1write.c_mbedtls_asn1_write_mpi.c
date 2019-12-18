#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int s; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBEDTLS_ASN1_INTEGER ; 
 int MBEDTLS_ERR_ASN1_BUF_TOO_SMALL ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_len (unsigned char**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_tag (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 
 size_t mbedtls_mpi_size (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_write_binary (TYPE_1__ const*,unsigned char*,size_t) ; 

int mbedtls_asn1_write_mpi( unsigned char **p, unsigned char *start, const mbedtls_mpi *X )
{
    int ret;
    size_t len = 0;

    /* Write the MPI */
    len = mbedtls_mpi_size( X );

    if( *p < start || (size_t)( *p - start ) < len )
        return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

    (*p) -= len;
    MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( X, *p, len ) );

    /* DER format assumes 2s complement for numbers, so the leftmost bit
     * should be 0 for positive numbers and 1 for negative numbers.
     */
    if( X->s ==1 && **p & 0x80 )
    {
        if( *p - start < 1 )
            return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

        *--(*p) = 0x00;
        len += 1;
    }

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( p, start, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( p, start, MBEDTLS_ASN1_INTEGER ) );

    ret = (int) len;

cleanup:
    return( ret );
}