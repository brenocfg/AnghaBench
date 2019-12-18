#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ in_msglen; scalar_t__ in_hslen; int* in_msg; TYPE_2__* handshake; TYPE_1__* conf; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_9__ {unsigned int in_msg_seq; int in_flight_start_seq; int /*<<< orphan*/ * hs_msg; } ;
struct TYPE_8__ {scalar_t__ transport; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_SSL_INVALID_RECORD ; 
 int MBEDTLS_ERR_SSL_WANT_READ ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 int MBEDTLS_SSL_HS_HELLO_VERIFY_REQUEST ; 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 scalar_t__ mbedtls_ssl_hs_hdr_len (TYPE_3__*) ; 
 int mbedtls_ssl_resend (TYPE_3__*) ; 
 scalar_t__ memcmp (int*,char*,int) ; 
 int ssl_reassemble_dtls_handshake (TYPE_3__*) ; 

int mbedtls_ssl_prepare_handshake_record( mbedtls_ssl_context *ssl )
{
    if( ssl->in_msglen < mbedtls_ssl_hs_hdr_len( ssl ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "handshake message too short: %d",
                            ssl->in_msglen ) );
        return( MBEDTLS_ERR_SSL_INVALID_RECORD );
    }

    ssl->in_hslen = mbedtls_ssl_hs_hdr_len( ssl ) + (
                    ( ssl->in_msg[1] << 16 ) |
                    ( ssl->in_msg[2] << 8  ) |
                      ssl->in_msg[3] );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "handshake message: msglen ="
                        " %d, type = %d, hslen = %d",
                        ssl->in_msglen, ssl->in_msg[0], ssl->in_hslen ) );

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        int ret;
        unsigned int recv_msg_seq = ( ssl->in_msg[4] << 8 ) | ssl->in_msg[5];

        /* ssl->handshake is NULL when receiving ClientHello for renego */
        if( ssl->handshake != NULL &&
            recv_msg_seq != ssl->handshake->in_msg_seq )
        {
            /* Retransmit only on last message from previous flight, to avoid
             * too many retransmissions.
             * Besides, No sane server ever retransmits HelloVerifyRequest */
            if( recv_msg_seq == ssl->handshake->in_flight_start_seq - 1 &&
                ssl->in_msg[0] != MBEDTLS_SSL_HS_HELLO_VERIFY_REQUEST )
            {
                MBEDTLS_SSL_DEBUG_MSG( 2, ( "received message from last flight, "
                                    "message_seq = %d, start_of_flight = %d",
                                    recv_msg_seq,
                                    ssl->handshake->in_flight_start_seq ) );

                if( ( ret = mbedtls_ssl_resend( ssl ) ) != 0 )
                {
                    MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_resend", ret );
                    return( ret );
                }
            }
            else
            {
                MBEDTLS_SSL_DEBUG_MSG( 2, ( "dropping out-of-sequence message: "
                                    "message_seq = %d, expected = %d",
                                    recv_msg_seq,
                                    ssl->handshake->in_msg_seq ) );
            }

            return( MBEDTLS_ERR_SSL_WANT_READ );
        }
        /* Wait until message completion to increment in_msg_seq */

        /* Reassemble if current message is fragmented or reassembly is
         * already in progress */
        if( ssl->in_msglen < ssl->in_hslen ||
            memcmp( ssl->in_msg + 6, "\0\0\0",        3 ) != 0 ||
            memcmp( ssl->in_msg + 9, ssl->in_msg + 1, 3 ) != 0 ||
            ( ssl->handshake != NULL && ssl->handshake->hs_msg != NULL ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 2, ( "found fragmented DTLS handshake message" ) );

            if( ( ret = ssl_reassemble_dtls_handshake( ssl ) ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "ssl_reassemble_dtls_handshake", ret );
                return( ret );
            }
        }
    }
    else
#endif /* MBEDTLS_SSL_PROTO_DTLS */
    /* With TLS we don't handle fragmentation (for now) */
    if( ssl->in_msglen < ssl->in_hslen )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "TLS handshake fragmentation not supported" ) );
        return( MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE );
    }

    return( 0 );
}