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
struct TYPE_7__ {scalar_t__ version; struct TYPE_7__* next; } ;
typedef  TYPE_1__ mbedtls_x509_crt ;

/* Variables and functions */
 int MBEDTLS_ERR_X509_ALLOC_FAILED ; 
 int MBEDTLS_ERR_X509_BAD_INPUT_DATA ; 
 TYPE_1__* mbedtls_calloc (int,int) ; 
 int /*<<< orphan*/  mbedtls_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_init (TYPE_1__*) ; 
 int x509_crt_parse_der_core (TYPE_1__*,unsigned char const*,size_t) ; 

int mbedtls_x509_crt_parse_der( mbedtls_x509_crt *chain, const unsigned char *buf,
                        size_t buflen )
{
    int ret;
    mbedtls_x509_crt *crt = chain, *prev = NULL;

    /*
     * Check for valid input
     */
    if( crt == NULL || buf == NULL )
        return( MBEDTLS_ERR_X509_BAD_INPUT_DATA );

    while( crt->version != 0 && crt->next != NULL )
    {
        prev = crt;
        crt = crt->next;
    }

    /*
     * Add new certificate on the end of the chain if needed.
     */
    if( crt->version != 0 && crt->next == NULL )
    {
        crt->next = mbedtls_calloc( 1, sizeof( mbedtls_x509_crt ) );

        if( crt->next == NULL )
            return( MBEDTLS_ERR_X509_ALLOC_FAILED );

        prev = crt;
        mbedtls_x509_crt_init( crt->next );
        crt = crt->next;
    }

    if( ( ret = x509_crt_parse_der_core( crt, buf, buflen ) ) != 0 )
    {
        if( prev )
            prev->next = NULL;

        if( crt != chain )
            mbedtls_free( crt );

        return( ret );
    }

    return( 0 );
}