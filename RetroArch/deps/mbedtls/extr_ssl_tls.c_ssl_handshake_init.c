#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  retransmit_state; int /*<<< orphan*/  alt_transform_out; } ;
typedef  TYPE_2__ mbedtls_ssl_transform ;
typedef  TYPE_2__ mbedtls_ssl_session ;
typedef  TYPE_2__ mbedtls_ssl_handshake_params ;
struct TYPE_17__ {TYPE_2__* handshake; TYPE_1__* conf; int /*<<< orphan*/  transform_out; TYPE_2__* transform_negotiate; TYPE_2__* session_negotiate; } ;
typedef  TYPE_5__ mbedtls_ssl_context ;
struct TYPE_15__ {scalar_t__ transport; scalar_t__ endpoint; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_ALLOC_FAILED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ MBEDTLS_SSL_IS_CLIENT ; 
 int /*<<< orphan*/  MBEDTLS_SSL_RETRANS_PREPARING ; 
 int /*<<< orphan*/  MBEDTLS_SSL_RETRANS_WAITING ; 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 scalar_t__ mbedtls_calloc (int,int) ; 
 int /*<<< orphan*/  mbedtls_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_handshake_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_session_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_session_init (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_transform_free (TYPE_2__*) ; 
 int /*<<< orphan*/  ssl_handshake_params_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ssl_set_timer (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_transform_init (TYPE_2__*) ; 

__attribute__((used)) static int ssl_handshake_init( mbedtls_ssl_context *ssl )
{
    /* Clear old handshake information if present */
    if( ssl->transform_negotiate )
        mbedtls_ssl_transform_free( ssl->transform_negotiate );
    if( ssl->session_negotiate )
        mbedtls_ssl_session_free( ssl->session_negotiate );
    if( ssl->handshake )
        mbedtls_ssl_handshake_free( ssl->handshake );

    /*
     * Either the pointers are now NULL or cleared properly and can be freed.
     * Now allocate missing structures.
     */
    if( ssl->transform_negotiate == NULL )
    {
        ssl->transform_negotiate = (mbedtls_ssl_transform*)mbedtls_calloc( 1, sizeof(mbedtls_ssl_transform) );
    }

    if( ssl->session_negotiate == NULL )
    {
        ssl->session_negotiate = (mbedtls_ssl_session*)mbedtls_calloc( 1, sizeof(mbedtls_ssl_session) );
    }

    if( ssl->handshake == NULL )
    {
        ssl->handshake = (mbedtls_ssl_handshake_params*)mbedtls_calloc( 1, sizeof(mbedtls_ssl_handshake_params) );
    }

    /* All pointers should exist and can be directly freed without issue */
    if( ssl->handshake == NULL ||
        ssl->transform_negotiate == NULL ||
        ssl->session_negotiate == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "alloc() of ssl sub-contexts failed" ) );

        mbedtls_free( ssl->handshake );
        mbedtls_free( ssl->transform_negotiate );
        mbedtls_free( ssl->session_negotiate );

        ssl->handshake = NULL;
        ssl->transform_negotiate = NULL;
        ssl->session_negotiate = NULL;

        return( MBEDTLS_ERR_SSL_ALLOC_FAILED );
    }

    /* Initialize structures */
    mbedtls_ssl_session_init( ssl->session_negotiate );
    ssl_transform_init( ssl->transform_negotiate );
    ssl_handshake_params_init( ssl->handshake );

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        ssl->handshake->alt_transform_out = ssl->transform_out;

        if( ssl->conf->endpoint == MBEDTLS_SSL_IS_CLIENT )
            ssl->handshake->retransmit_state = MBEDTLS_SSL_RETRANS_PREPARING;
        else
            ssl->handshake->retransmit_state = MBEDTLS_SSL_RETRANS_WAITING;

        ssl_set_timer( ssl, 0 );
    }
#endif

    return( 0 );
}