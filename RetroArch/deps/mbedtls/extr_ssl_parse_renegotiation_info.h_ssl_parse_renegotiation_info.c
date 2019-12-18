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
struct TYPE_4__ {scalar_t__ renego_status; int verify_data_len; int /*<<< orphan*/  secure_renegotiation; int /*<<< orphan*/  peer_verify_data; } ;
typedef  TYPE_1__ mbedtls_ssl_context ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ MBEDTLS_SSL_INITIAL_HANDSHAKE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_SECURE_RENEGOTIATION ; 
 scalar_t__ mbedtls_ssl_safer_memcmp (unsigned char const*,int /*<<< orphan*/ ,unsigned char const) ; 
 int /*<<< orphan*/  mbedtls_ssl_send_alert_message (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_parse_renegotiation_info( mbedtls_ssl_context *ssl,
                                         const unsigned char *buf,
                                         size_t len )
{
#if defined(MBEDTLS_SSL_RENEGOTIATION)
    if( ssl->renego_status != MBEDTLS_SSL_INITIAL_HANDSHAKE )
    {
        /* Check verify-data in constant-time. The length OTOH is no secret */
        if( len    != 1 + ssl->verify_data_len ||
            buf[0] !=     ssl->verify_data_len ||
            mbedtls_ssl_safer_memcmp( buf + 1, ssl->peer_verify_data,
                          ssl->verify_data_len ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "non-matching renegotiation info" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
        }
    }
    else
#endif /* MBEDTLS_SSL_RENEGOTIATION */
    {
        if( len != 1 || buf[0] != 0x0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "non-zero length renegotiation info" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
        }

        ssl->secure_renegotiation = MBEDTLS_SSL_SECURE_RENEGOTIATION;
    }

    return( 0 );
}