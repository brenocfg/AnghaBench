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
typedef  int /*<<< orphan*/  mbedtls_x509_crl ;
struct TYPE_5__ {unsigned char const* buf; size_t buflen; } ;
typedef  TYPE_1__ mbedtls_pem_context ;

/* Variables and functions */
 int MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT ; 
 int MBEDTLS_ERR_X509_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  mbedtls_pem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_pem_init (TYPE_1__*) ; 
 int mbedtls_pem_read_buffer (TYPE_1__*,char*,char*,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int mbedtls_x509_crl_parse_der (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int mbedtls_x509_crl_parse( mbedtls_x509_crl *chain, const unsigned char *buf, size_t buflen )
{
#if defined(MBEDTLS_PEM_PARSE_C)
    int ret;
    size_t use_len;
    mbedtls_pem_context pem;
    int is_pem = 0;

    if( chain == NULL || buf == NULL )
        return( MBEDTLS_ERR_X509_BAD_INPUT_DATA );

    do
    {
        mbedtls_pem_init( &pem );

        /* Avoid calling mbedtls_pem_read_buffer() on non-null-terminated
         * string */
        if( buflen == 0 || buf[buflen - 1] != '\0' )
            ret = MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT;
        else
            ret = mbedtls_pem_read_buffer( &pem,
                                           "-----BEGIN X509 CRL-----",
                                           "-----END X509 CRL-----",
                                            buf, NULL, 0, &use_len );

        if( ret == 0 )
        {
            /*
             * Was PEM encoded
             */
            is_pem = 1;

            buflen -= use_len;
            buf += use_len;

            if( ( ret = mbedtls_x509_crl_parse_der( chain,
                                            pem.buf, pem.buflen ) ) != 0 )
            {
                mbedtls_pem_free( &pem );
                return( ret );
            }
        }
        else if( is_pem )
        {
            mbedtls_pem_free( &pem );
            return( ret );
        }

        mbedtls_pem_free( &pem );
    }
    /* In the PEM case, buflen is 1 at the end, for the terminated NULL byte.
     * And a valid CRL cannot be less than 1 byte anyway. */
    while( is_pem && buflen > 1 );

    if( is_pem )
        return( 0 );
    else
#endif /* MBEDTLS_PEM_PARSE_C */
        return( mbedtls_x509_crl_parse_der( chain, buf, buflen ) );
}