#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int state; TYPE_2__* handshake; TYPE_1__* conf; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_23__ {scalar_t__ retransmit_state; int /*<<< orphan*/  new_session_ticket; } ;
struct TYPE_22__ {scalar_t__ transport; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED ; 
#define  MBEDTLS_SSL_CERTIFICATE_REQUEST 144 
#define  MBEDTLS_SSL_CERTIFICATE_VERIFY 143 
#define  MBEDTLS_SSL_CLIENT_CERTIFICATE 142 
#define  MBEDTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC 141 
#define  MBEDTLS_SSL_CLIENT_FINISHED 140 
#define  MBEDTLS_SSL_CLIENT_HELLO 139 
#define  MBEDTLS_SSL_CLIENT_KEY_EXCHANGE 138 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
#define  MBEDTLS_SSL_FLUSH_BUFFERS 137 
 int MBEDTLS_SSL_HANDSHAKE_OVER ; 
#define  MBEDTLS_SSL_HANDSHAKE_WRAPUP 136 
#define  MBEDTLS_SSL_HELLO_REQUEST 135 
 scalar_t__ MBEDTLS_SSL_RETRANS_SENDING ; 
#define  MBEDTLS_SSL_SERVER_CERTIFICATE 134 
#define  MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC 133 
#define  MBEDTLS_SSL_SERVER_FINISHED 132 
#define  MBEDTLS_SSL_SERVER_HELLO 131 
#define  MBEDTLS_SSL_SERVER_HELLO_DONE 130 
#define  MBEDTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT 129 
#define  MBEDTLS_SSL_SERVER_KEY_EXCHANGE 128 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 int mbedtls_ssl_flush_output (TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_handshake_wrapup (TYPE_3__*) ; 
 int mbedtls_ssl_parse_certificate (TYPE_3__*) ; 
 int mbedtls_ssl_parse_change_cipher_spec (TYPE_3__*) ; 
 int mbedtls_ssl_parse_finished (TYPE_3__*) ; 
 int mbedtls_ssl_resend (TYPE_3__*) ; 
 int mbedtls_ssl_write_certificate (TYPE_3__*) ; 
 int mbedtls_ssl_write_change_cipher_spec (TYPE_3__*) ; 
 int mbedtls_ssl_write_finished (TYPE_3__*) ; 
 int ssl_parse_certificate_verify (TYPE_3__*) ; 
 int ssl_parse_client_hello (TYPE_3__*) ; 
 int ssl_parse_client_key_exchange (TYPE_3__*) ; 
 int ssl_write_certificate_request (TYPE_3__*) ; 
 int ssl_write_new_session_ticket (TYPE_3__*) ; 
 int ssl_write_server_hello (TYPE_3__*) ; 
 int ssl_write_server_hello_done (TYPE_3__*) ; 
 int ssl_write_server_key_exchange (TYPE_3__*) ; 

int mbedtls_ssl_handshake_server_step( mbedtls_ssl_context *ssl )
{
    int ret = 0;

    if( ssl->state == MBEDTLS_SSL_HANDSHAKE_OVER || ssl->handshake == NULL )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "server state: %d", ssl->state ) );

    if( ( ret = mbedtls_ssl_flush_output( ssl ) ) != 0 )
        return( ret );

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake->retransmit_state == MBEDTLS_SSL_RETRANS_SENDING )
    {
        if( ( ret = mbedtls_ssl_resend( ssl ) ) != 0 )
            return( ret );
    }
#endif

    switch( ssl->state )
    {
        case MBEDTLS_SSL_HELLO_REQUEST:
            ssl->state = MBEDTLS_SSL_CLIENT_HELLO;
            break;

        /*
         *  <==   ClientHello
         */
        case MBEDTLS_SSL_CLIENT_HELLO:
            ret = ssl_parse_client_hello( ssl );
            break;

#if defined(MBEDTLS_SSL_PROTO_DTLS)
        case MBEDTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT:
            return( MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED );
#endif

        /*
         *  ==>   ServerHello
         *        Certificate
         *      ( ServerKeyExchange  )
         *      ( CertificateRequest )
         *        ServerHelloDone
         */
        case MBEDTLS_SSL_SERVER_HELLO:
            ret = ssl_write_server_hello( ssl );
            break;

        case MBEDTLS_SSL_SERVER_CERTIFICATE:
            ret = mbedtls_ssl_write_certificate( ssl );
            break;

        case MBEDTLS_SSL_SERVER_KEY_EXCHANGE:
            ret = ssl_write_server_key_exchange( ssl );
            break;

        case MBEDTLS_SSL_CERTIFICATE_REQUEST:
            ret = ssl_write_certificate_request( ssl );
            break;

        case MBEDTLS_SSL_SERVER_HELLO_DONE:
            ret = ssl_write_server_hello_done( ssl );
            break;

        /*
         *  <== ( Certificate/Alert  )
         *        ClientKeyExchange
         *      ( CertificateVerify  )
         *        ChangeCipherSpec
         *        Finished
         */
        case MBEDTLS_SSL_CLIENT_CERTIFICATE:
            ret = mbedtls_ssl_parse_certificate( ssl );
            break;

        case MBEDTLS_SSL_CLIENT_KEY_EXCHANGE:
            ret = ssl_parse_client_key_exchange( ssl );
            break;

        case MBEDTLS_SSL_CERTIFICATE_VERIFY:
            ret = ssl_parse_certificate_verify( ssl );
            break;

        case MBEDTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC:
            ret = mbedtls_ssl_parse_change_cipher_spec( ssl );
            break;

        case MBEDTLS_SSL_CLIENT_FINISHED:
            ret = mbedtls_ssl_parse_finished( ssl );
            break;

        /*
         *  ==> ( NewSessionTicket )
         *        ChangeCipherSpec
         *        Finished
         */
        case MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC:
#if defined(MBEDTLS_SSL_SESSION_TICKETS)
            if( ssl->handshake->new_session_ticket != 0 )
                ret = ssl_write_new_session_ticket( ssl );
            else
#endif
                ret = mbedtls_ssl_write_change_cipher_spec( ssl );
            break;

        case MBEDTLS_SSL_SERVER_FINISHED:
            ret = mbedtls_ssl_write_finished( ssl );
            break;

        case MBEDTLS_SSL_FLUSH_BUFFERS:
            MBEDTLS_SSL_DEBUG_MSG( 2, ( "handshake: done" ) );
            ssl->state = MBEDTLS_SSL_HANDSHAKE_WRAPUP;
            break;

        case MBEDTLS_SSL_HANDSHAKE_WRAPUP:
            mbedtls_ssl_handshake_wrapup( ssl );
            break;

        default:
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "invalid state %d", ssl->state ) );
            return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );
    }

    return( ret );
}