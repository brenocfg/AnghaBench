#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* peer_cert; } ;
typedef  TYPE_3__ mbedtls_ssl_session ;
struct TYPE_6__ {size_t len; TYPE_3__ const* p; } ;
struct TYPE_7__ {TYPE_1__ raw; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  memcpy (unsigned char*,TYPE_3__ const*,size_t) ; 

__attribute__((used)) static int ssl_save_session( const mbedtls_ssl_session *session,
                             unsigned char *buf, size_t buf_len,
                             size_t *olen )
{
    unsigned char *p = buf;
    size_t left = buf_len;
#if defined(MBEDTLS_X509_CRT_PARSE_C)
    size_t cert_len;
#endif /* MBEDTLS_X509_CRT_PARSE_C */

    if( left < sizeof( mbedtls_ssl_session ) )
        return( MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL );

    memcpy( p, session, sizeof( mbedtls_ssl_session ) );
    p += sizeof( mbedtls_ssl_session );
    left -= sizeof( mbedtls_ssl_session );

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    if( session->peer_cert == NULL )
        cert_len = 0;
    else
        cert_len = session->peer_cert->raw.len;

    if( left < 3 + cert_len )
        return( MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL );

    *p++ = (unsigned char)( cert_len >> 16 & 0xFF );
    *p++ = (unsigned char)( cert_len >>  8 & 0xFF );
    *p++ = (unsigned char)( cert_len       & 0xFF );

    if( session->peer_cert != NULL )
        memcpy( p, session->peer_cert->raw.p, cert_len );

    p += cert_len;
#endif /* MBEDTLS_X509_CRT_PARSE_C */

    *olen = p - buf;

    return( 0 );
}