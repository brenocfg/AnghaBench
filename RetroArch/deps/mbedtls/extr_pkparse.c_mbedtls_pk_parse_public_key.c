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
typedef  int /*<<< orphan*/  mbedtls_pk_context ;
struct TYPE_5__ {unsigned char* buf; size_t buflen; } ;
typedef  TYPE_1__ mbedtls_pem_context ;

/* Variables and functions */
 int MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT ; 
 int /*<<< orphan*/  mbedtls_pem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_pem_init (TYPE_1__*) ; 
 int mbedtls_pem_read_buffer (TYPE_1__*,char*,char*,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int mbedtls_pk_parse_subpubkey (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 

int mbedtls_pk_parse_public_key( mbedtls_pk_context *ctx,
                         const unsigned char *key, size_t keylen )
{
    int ret;
    unsigned char *p;
#if defined(MBEDTLS_PEM_PARSE_C)
    size_t len;
    mbedtls_pem_context pem;

    mbedtls_pem_init( &pem );

    /* Avoid calling mbedtls_pem_read_buffer() on non-null-terminated string */
    if( keylen == 0 || key[keylen - 1] != '\0' )
        ret = MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT;
    else
        ret = mbedtls_pem_read_buffer( &pem,
                "-----BEGIN PUBLIC KEY-----",
                "-----END PUBLIC KEY-----",
                key, NULL, 0, &len );

    if( ret == 0 )
    {
        /*
         * Was PEM encoded
         */
        key = pem.buf;
        keylen = pem.buflen;
    }
    else if( ret != MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT )
    {
        mbedtls_pem_free( &pem );
        return( ret );
    }
#endif /* MBEDTLS_PEM_PARSE_C */
    p = (unsigned char *) key;

    ret = mbedtls_pk_parse_subpubkey( &p, p + keylen, ctx );

#if defined(MBEDTLS_PEM_PARSE_C)
    mbedtls_pem_free( &pem );
#endif

    return( ret );
}