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
typedef  int uint32_t ;
typedef  scalar_t__ tlen ;
struct TYPE_8__ {int* out_msg; int out_msglen; TYPE_2__* handshake; int /*<<< orphan*/  session_negotiate; TYPE_1__* conf; int /*<<< orphan*/  out_msgtype; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
typedef  int lifetime ;
struct TYPE_7__ {scalar_t__ new_session_ticket; } ;
struct TYPE_6__ {int (* f_ticket_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,size_t*,int*) ;int /*<<< orphan*/  p_ticket; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 int MBEDTLS_SSL_HS_NEW_SESSION_TICKET ; 
 int MBEDTLS_SSL_MAX_CONTENT_LEN ; 
 int /*<<< orphan*/  MBEDTLS_SSL_MSG_HANDSHAKE ; 
 int mbedtls_ssl_write_record (TYPE_3__*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,size_t*,int*) ; 

__attribute__((used)) static int ssl_write_new_session_ticket( mbedtls_ssl_context *ssl )
{
    int ret;
    size_t tlen;
    uint32_t lifetime;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write new session ticket" ) );

    ssl->out_msgtype = MBEDTLS_SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = MBEDTLS_SSL_HS_NEW_SESSION_TICKET;

    /*
     * struct {
     *     uint32 ticket_lifetime_hint;
     *     opaque ticket<0..2^16-1>;
     * } NewSessionTicket;
     *
     * 4  .  7   ticket_lifetime_hint (0 = unspecified)
     * 8  .  9   ticket_len (n)
     * 10 .  9+n ticket content
     */

    if( ( ret = ssl->conf->f_ticket_write( ssl->conf->p_ticket,
                                ssl->session_negotiate,
                                ssl->out_msg + 10,
                                ssl->out_msg + MBEDTLS_SSL_MAX_CONTENT_LEN,
                                &tlen, &lifetime ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_ticket_write", ret );
        tlen = 0;
    }

    ssl->out_msg[4] = ( lifetime >> 24 ) & 0xFF;
    ssl->out_msg[5] = ( lifetime >> 16 ) & 0xFF;
    ssl->out_msg[6] = ( lifetime >>  8 ) & 0xFF;
    ssl->out_msg[7] = ( lifetime       ) & 0xFF;

    ssl->out_msg[8] = (unsigned char)( ( tlen >> 8 ) & 0xFF );
    ssl->out_msg[9] = (unsigned char)( ( tlen      ) & 0xFF );

    ssl->out_msglen = 10 + tlen;

    /*
     * Morally equivalent to updating ssl->state, but NewSessionTicket and
     * ChangeCipherSpec share the same state.
     */
    ssl->handshake->new_session_ticket = 0;

    if( ( ret = mbedtls_ssl_write_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_write_record", ret );
        return( ret );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write new session ticket" ) );

    return( 0 );
}