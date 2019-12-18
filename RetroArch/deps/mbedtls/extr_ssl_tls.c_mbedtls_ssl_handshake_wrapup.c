#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ renego_status; int /*<<< orphan*/  state; TYPE_2__* handshake; TYPE_1__* conf; TYPE_4__* session; TYPE_4__* session_negotiate; scalar_t__ renego_records_seen; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_13__ {scalar_t__ id_len; int /*<<< orphan*/  encrypt_then_mac; } ;
struct TYPE_11__ {int resume; int /*<<< orphan*/ * flight; } ;
struct TYPE_10__ {scalar_t__ (* f_set_cache ) (int /*<<< orphan*/ ,TYPE_4__*) ;scalar_t__ transport; int /*<<< orphan*/  p_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ MBEDTLS_SSL_RENEGOTIATION_DONE ; 
 scalar_t__ MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS ; 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 int /*<<< orphan*/  mbedtls_free (TYPE_4__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_session_free (TYPE_4__*) ; 
 int /*<<< orphan*/  ssl_handshake_wrapup_free_hs_transform (TYPE_3__*) ; 
 int /*<<< orphan*/  ssl_set_timer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 

void mbedtls_ssl_handshake_wrapup( mbedtls_ssl_context *ssl )
{
    int resume = ssl->handshake->resume;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "=> handshake wrapup" ) );

#if defined(MBEDTLS_SSL_RENEGOTIATION)
    if( ssl->renego_status == MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS )
    {
        ssl->renego_status =  MBEDTLS_SSL_RENEGOTIATION_DONE;
        ssl->renego_records_seen = 0;
    }
#endif

    /*
     * Free the previous session and switch in the current one
     */
    if( ssl->session )
    {
#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
        /* RFC 7366 3.1: keep the EtM state */
        ssl->session_negotiate->encrypt_then_mac =
                  ssl->session->encrypt_then_mac;
#endif

        mbedtls_ssl_session_free( ssl->session );
        mbedtls_free( ssl->session );
    }
    ssl->session = ssl->session_negotiate;
    ssl->session_negotiate = NULL;

    /*
     * Add cache entry
     */
    if( ssl->conf->f_set_cache != NULL &&
        ssl->session->id_len != 0 &&
        resume == 0 )
    {
        if( ssl->conf->f_set_cache( ssl->conf->p_cache, ssl->session ) != 0 )
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "cache did not store session" ) );
    }

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake->flight != NULL )
    {
        /* Cancel handshake timer */
        ssl_set_timer( ssl, 0 );

        /* Keep last flight around in case we need to resend it:
         * we need the handshake and transform structures for that */
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "skip freeing handshake and transform" ) );
    }
    else
#endif
        ssl_handshake_wrapup_free_hs_transform( ssl );

    ssl->state++;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "<= handshake wrapup" ) );
}