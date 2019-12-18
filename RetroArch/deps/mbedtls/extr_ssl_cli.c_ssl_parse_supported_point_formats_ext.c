#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* handshake; } ;
typedef  TYPE_4__ mbedtls_ssl_context ;
struct TYPE_8__ {unsigned char point_format; } ;
struct TYPE_7__ {unsigned char point_format; } ;
struct TYPE_9__ {TYPE_2__ ecjpake_ctx; TYPE_1__ ecdh_ctx; } ;

/* Variables and functions */
 unsigned char const MBEDTLS_ECP_PF_COMPRESSED ; 
 unsigned char const MBEDTLS_ECP_PF_UNCOMPRESSED ; 
 int MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  mbedtls_ssl_send_alert_message (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_parse_supported_point_formats_ext( mbedtls_ssl_context *ssl,
                                                  const unsigned char *buf,
                                                  size_t len )
{
    size_t list_size;
    const unsigned char *p;

    list_size = buf[0];
    if( list_size + 1 != len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server hello message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO );
    }

    p = buf + 1;
    while( list_size > 0 )
    {
        if( p[0] == MBEDTLS_ECP_PF_UNCOMPRESSED ||
            p[0] == MBEDTLS_ECP_PF_COMPRESSED )
        {
#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C)
            ssl->handshake->ecdh_ctx.point_format = p[0];
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
            ssl->handshake->ecjpake_ctx.point_format = p[0];
#endif
            MBEDTLS_SSL_DEBUG_MSG( 4, ( "point format selected: %d", p[0] ) );
            return( 0 );
        }

        list_size--;
        p++;
    }

    MBEDTLS_SSL_DEBUG_MSG( 1, ( "no point format in common" ) );
    mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                    MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE );
    return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO );
}