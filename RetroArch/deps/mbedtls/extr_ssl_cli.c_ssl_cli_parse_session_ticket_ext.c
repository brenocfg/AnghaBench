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
struct TYPE_8__ {TYPE_2__* handshake; TYPE_1__* conf; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_7__ {int new_session_ticket; } ;
struct TYPE_6__ {scalar_t__ session_tickets; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ MBEDTLS_SSL_SESSION_TICKETS_DISABLED ; 
 int /*<<< orphan*/  mbedtls_ssl_send_alert_message (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_cli_parse_session_ticket_ext( mbedtls_ssl_context *ssl,
                                         const unsigned char *buf,
                                         size_t len )
{
    if( ssl->conf->session_tickets == MBEDTLS_SSL_SESSION_TICKETS_DISABLED ||
        len != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "non-matching session ticket extension" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE );
        return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO );
    }

    ((void) buf);

    ssl->handshake->new_session_ticket = 1;

    return( 0 );
}