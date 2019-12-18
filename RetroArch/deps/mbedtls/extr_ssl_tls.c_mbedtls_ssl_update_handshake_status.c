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
struct TYPE_8__ {scalar_t__ state; TYPE_2__* handshake; TYPE_1__* conf; int /*<<< orphan*/  in_hslen; int /*<<< orphan*/  in_msg; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_7__ {int /*<<< orphan*/  in_msg_seq; int /*<<< orphan*/  (* update_checksum ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ transport; } ;

/* Variables and functions */
 scalar_t__ MBEDTLS_SSL_HANDSHAKE_OVER ; 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mbedtls_ssl_update_handshake_status( mbedtls_ssl_context *ssl )
{

    if( ssl->state != MBEDTLS_SSL_HANDSHAKE_OVER &&
        ssl->handshake != NULL )
    {
        ssl->handshake->update_checksum( ssl, ssl->in_msg, ssl->in_hslen );
    }

    /* Handshake message is complete, increment counter */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake != NULL )
    {
        ssl->handshake->in_msg_seq++;
    }
#endif
}