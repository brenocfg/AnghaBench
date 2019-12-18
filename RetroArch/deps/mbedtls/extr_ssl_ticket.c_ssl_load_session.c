#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;
struct TYPE_4__ {int /*<<< orphan*/ * peer_cert; } ;
typedef  TYPE_1__ mbedtls_ssl_session ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_ALLOC_FAILED ; 
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 int /*<<< orphan*/ * mbedtls_calloc (int,int) ; 
 int /*<<< orphan*/  mbedtls_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_init (int /*<<< orphan*/ *) ; 
 int mbedtls_x509_crt_parse_der (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,unsigned char const*,int) ; 

__attribute__((used)) static int ssl_load_session( mbedtls_ssl_session *session,
                             const unsigned char *buf, size_t len )
{
    const unsigned char *p = buf;
    const unsigned char * const end = buf + len;
#if defined(MBEDTLS_X509_CRT_PARSE_C)
    size_t cert_len;
#endif /* MBEDTLS_X509_CRT_PARSE_C */

    if( p + sizeof( mbedtls_ssl_session ) > end )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    memcpy( session, p, sizeof( mbedtls_ssl_session ) );
    p += sizeof( mbedtls_ssl_session );

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    if( p + 3 > end )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    cert_len = ( p[0] << 16 ) | ( p[1] << 8 ) | p[2];
    p += 3;

    if( cert_len == 0 )
    {
        session->peer_cert = NULL;
    }
    else
    {
        int ret;

        if( p + cert_len > end )
            return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

        session->peer_cert = mbedtls_calloc( 1, sizeof( mbedtls_x509_crt ) );

        if( session->peer_cert == NULL )
            return( MBEDTLS_ERR_SSL_ALLOC_FAILED );

        mbedtls_x509_crt_init( session->peer_cert );

        if( ( ret = mbedtls_x509_crt_parse_der( session->peer_cert,
                                        p, cert_len ) ) != 0 )
        {
            mbedtls_x509_crt_free( session->peer_cert );
            mbedtls_free( session->peer_cert );
            session->peer_cert = NULL;
            return( ret );
        }

        p += cert_len;
    }
#endif /* MBEDTLS_X509_CRT_PARSE_C */

    if( p != end )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    return( 0 );
}