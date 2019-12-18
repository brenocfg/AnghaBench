#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ in_msgtype; scalar_t__* in_msg; TYPE_1__* handshake; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_5__ {int /*<<< orphan*/  retransmit_state; int /*<<< orphan*/  in_msg_seq; int /*<<< orphan*/  in_flight_start_seq; int /*<<< orphan*/ * cur_msg; int /*<<< orphan*/ * flight; } ;

/* Variables and functions */
 scalar_t__ MBEDTLS_SSL_HS_FINISHED ; 
 scalar_t__ MBEDTLS_SSL_MSG_HANDSHAKE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_RETRANS_FINISHED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_RETRANS_PREPARING ; 
 int /*<<< orphan*/  ssl_flight_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_set_timer (TYPE_2__*,int /*<<< orphan*/ ) ; 

void mbedtls_ssl_recv_flight_completed( mbedtls_ssl_context *ssl )
{
    /* We won't need to resend that one any more */
    ssl_flight_free( ssl->handshake->flight );
    ssl->handshake->flight = NULL;
    ssl->handshake->cur_msg = NULL;

    /* The next incoming flight will start with this msg_seq */
    ssl->handshake->in_flight_start_seq = ssl->handshake->in_msg_seq;

    /* Cancel timer */
    ssl_set_timer( ssl, 0 );

    if( ssl->in_msgtype == MBEDTLS_SSL_MSG_HANDSHAKE &&
        ssl->in_msg[0] == MBEDTLS_SSL_HS_FINISHED )
    {
        ssl->handshake->retransmit_state = MBEDTLS_SSL_RETRANS_FINISHED;
    }
    else
        ssl->handshake->retransmit_state = MBEDTLS_SSL_RETRANS_PREPARING;
}