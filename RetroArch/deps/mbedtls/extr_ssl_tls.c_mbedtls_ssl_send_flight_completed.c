#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ in_msgtype; scalar_t__* in_msg; TYPE_1__* handshake; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_6__ {int /*<<< orphan*/  retransmit_state; int /*<<< orphan*/  retransmit_timeout; } ;

/* Variables and functions */
 scalar_t__ MBEDTLS_SSL_HS_FINISHED ; 
 scalar_t__ MBEDTLS_SSL_MSG_HANDSHAKE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_RETRANS_FINISHED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_RETRANS_WAITING ; 
 int /*<<< orphan*/  ssl_reset_retransmit_timeout (TYPE_2__*) ; 
 int /*<<< orphan*/  ssl_set_timer (TYPE_2__*,int /*<<< orphan*/ ) ; 

void mbedtls_ssl_send_flight_completed( mbedtls_ssl_context *ssl )
{
    ssl_reset_retransmit_timeout( ssl );
    ssl_set_timer( ssl, ssl->handshake->retransmit_timeout );

    if( ssl->in_msgtype == MBEDTLS_SSL_MSG_HANDSHAKE &&
        ssl->in_msg[0] == MBEDTLS_SSL_HS_FINISHED )
    {
        ssl->handshake->retransmit_state = MBEDTLS_SSL_RETRANS_FINISHED;
    }
    else
        ssl->handshake->retransmit_state = MBEDTLS_SSL_RETRANS_WAITING;
}