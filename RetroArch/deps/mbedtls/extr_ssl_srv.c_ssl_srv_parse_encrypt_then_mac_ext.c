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
struct TYPE_8__ {scalar_t__ minor_ver; TYPE_2__* session_negotiate; TYPE_1__* conf; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_7__ {scalar_t__ encrypt_then_mac; } ;
struct TYPE_6__ {scalar_t__ encrypt_then_mac; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ MBEDTLS_SSL_ETM_ENABLED ; 
 scalar_t__ MBEDTLS_SSL_MINOR_VERSION_0 ; 
 int /*<<< orphan*/  mbedtls_ssl_send_alert_message (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_srv_parse_encrypt_then_mac_ext( mbedtls_ssl_context *ssl,
                                      const unsigned char *buf,
                                      size_t len )
{
    if( len != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    ((void) buf);

    if( ssl->conf->encrypt_then_mac == MBEDTLS_SSL_ETM_ENABLED &&
        ssl->minor_ver != MBEDTLS_SSL_MINOR_VERSION_0 )
    {
        ssl->session_negotiate->encrypt_then_mac = MBEDTLS_SSL_ETM_ENABLED;
    }

    return( 0 );
}