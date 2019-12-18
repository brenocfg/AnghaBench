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
typedef  int /*<<< orphan*/  mbedtls_x509_csr ;
struct TYPE_5__ {unsigned char const* buf; size_t buflen; } ;
typedef  TYPE_1__ mbedtls_pem_context ;

/* Variables and functions */
 int MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT ; 
 int MBEDTLS_ERR_X509_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  mbedtls_pem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_pem_init (TYPE_1__*) ; 
 int mbedtls_pem_read_buffer (TYPE_1__*,char*,char*,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int mbedtls_x509_csr_parse_der (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int mbedtls_x509_csr_parse( mbedtls_x509_csr *csr, const unsigned char *buf, size_t buflen )
{
#if defined(MBEDTLS_PEM_PARSE_C)
    int ret;
    size_t use_len;
    mbedtls_pem_context pem;
#endif

    /*
     * Check for valid input
     */
    if( csr == NULL || buf == NULL || buflen == 0 )
        return( MBEDTLS_ERR_X509_BAD_INPUT_DATA );

#if defined(MBEDTLS_PEM_PARSE_C)
    mbedtls_pem_init( &pem );

    /* Avoid calling mbedtls_pem_read_buffer() on non-null-terminated string */
    if( buf[buflen - 1] != '\0' )
        ret = MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT;
    else
        ret = mbedtls_pem_read_buffer( &pem,
                               "-----BEGIN CERTIFICATE REQUEST-----",
                               "-----END CERTIFICATE REQUEST-----",
                               buf, NULL, 0, &use_len );

    if( ret == 0 )
    {
        /*
         * Was PEM encoded, parse the result
         */
        if( ( ret = mbedtls_x509_csr_parse_der( csr, pem.buf, pem.buflen ) ) != 0 )
            return( ret );

        mbedtls_pem_free( &pem );
        return( 0 );
    }
    else if( ret != MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT )
    {
        mbedtls_pem_free( &pem );
        return( ret );
    }
    else
#endif /* MBEDTLS_PEM_PARSE_C */
    return( mbedtls_x509_csr_parse_der( csr, buf, buflen ) );
}