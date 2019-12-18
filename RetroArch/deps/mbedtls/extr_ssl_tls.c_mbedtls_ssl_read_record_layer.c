#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ in_hslen; scalar_t__ in_msglen; scalar_t__* in_msg; scalar_t__ state; scalar_t__ badmac_seen; scalar_t__ in_msgtype; int /*<<< orphan*/ * handshake; TYPE_1__* conf; scalar_t__ in_left; void* next_record_offset; int /*<<< orphan*/ * in_offt; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_11__ {scalar_t__ transport; scalar_t__ badmac_limit; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_CLIENT_RECONNECT ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 int MBEDTLS_ERR_SSL_INVALID_MAC ; 
 int MBEDTLS_ERR_SSL_INVALID_RECORD ; 
 int MBEDTLS_ERR_SSL_UNEXPECTED_RECORD ; 
 int MBEDTLS_ERR_SSL_WANT_READ ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_BAD_RECORD_MAC ; 
 scalar_t__ MBEDTLS_SSL_CLIENT_FINISHED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_BUF (int,char*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 scalar_t__ MBEDTLS_SSL_HANDSHAKE_OVER ; 
 scalar_t__ MBEDTLS_SSL_HS_FINISHED ; 
 scalar_t__ MBEDTLS_SSL_MSG_HANDSHAKE ; 
 scalar_t__ MBEDTLS_SSL_SERVER_FINISHED ; 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 int mbedtls_ssl_fetch_input (TYPE_2__*,void*) ; 
 void* mbedtls_ssl_hdr_len (TYPE_2__*) ; 
 int mbedtls_ssl_resend (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_send_alert_message (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  ssl_handshake_wrapup_free_hs_transform (TYPE_2__*) ; 
 int ssl_parse_record_header (TYPE_2__*) ; 
 int ssl_prepare_record_content (TYPE_2__*) ; 

int mbedtls_ssl_read_record_layer( mbedtls_ssl_context *ssl )
{
    int ret;

    /*
     * Step A
     *
     * Consume last content-layer message and potentially
     * update in_msglen which keeps track of the contents'
     * consumption state.
     *
     * (1) Handshake messages:
     *     Remove last handshake message, move content
     *     and adapt in_msglen.
     *
     * (2) Alert messages:
     *     Consume whole record content, in_msglen = 0.
     *
     *     NOTE: This needs to be fixed, since like for
     *     handshake messages it is allowed to have
     *     multiple alerts witin a single record.
     *     Internal reference IOTSSL-1321.
     *
     * (3) Change cipher spec:
     *     Consume whole record content, in_msglen = 0.
     *
     * (4) Application data:
     *     Don't do anything - the record layer provides
     *     the application data as a stream transport
     *     and consumes through mbedtls_ssl_read only.
     *
     */

    /* Case (1): Handshake messages */
    if( ssl->in_hslen != 0 )
    {
        /* Hard assertion to be sure that no application data
         * is in flight, as corrupting ssl->in_msglen during
         * ssl->in_offt != NULL is fatal. */
        if( ssl->in_offt != NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }

        /*
         * Get next Handshake message in the current record
         */

        /* Notes:
         * (1) in_hslen is *NOT* necessarily the size of the
         *     current handshake content: If DTLS handshake
         *     fragmentation is used, that's the fragment
         *     size instead. Using the total handshake message
         *     size here is FAULTY and should be changed at
         *     some point. Internal reference IOTSSL-1414.
         * (2) While it doesn't seem to cause problems, one
         *     has to be very careful not to assume that in_hslen
         *     is always <= in_msglen in a sensible communication.
         *     Again, it's wrong for DTLS handshake fragmentation.
         *     The following check is therefore mandatory, and
         *     should not be treated as a silently corrected assertion.
         *     Additionally, ssl->in_hslen might be arbitrarily out of
         *     bounds after handling a DTLS message with an unexpected
         *     sequence number, see mbedtls_ssl_prepare_handshake_record.
         */
        if( ssl->in_hslen < ssl->in_msglen )
        {
            ssl->in_msglen -= ssl->in_hslen;
            memmove( ssl->in_msg, ssl->in_msg + ssl->in_hslen,
                     ssl->in_msglen );

            MBEDTLS_SSL_DEBUG_BUF( 4, "remaining content in record",
                                   ssl->in_msg, ssl->in_msglen );
        }
        else
        {
            ssl->in_msglen = 0;
        }

        ssl->in_hslen   = 0;
    }
    /* Case (4): Application data */
    else if( ssl->in_offt != NULL )
    {
        return( 0 );
    }
    /* Everything else (CCS & Alerts) */
    else
    {
        ssl->in_msglen = 0;
    }

    /*
     * Step B
     *
     * Fetch and decode new record if current one is fully consumed.
     *
     */

    if( ssl->in_msglen > 0 )
    {
        /* There's something left to be processed in the current record. */
        return( 0 );
    }

    /* Need to fetch a new record */

#if defined(MBEDTLS_SSL_PROTO_DTLS)
read_record_header:
#endif

    /* Current record either fully processed or to be discarded. */

    if( ( ret = mbedtls_ssl_fetch_input( ssl, mbedtls_ssl_hdr_len( ssl ) ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_fetch_input", ret );
        return( ret );
    }

    if( ( ret = ssl_parse_record_header( ssl ) ) != 0 )
    {
#if defined(MBEDTLS_SSL_PROTO_DTLS)
        if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
            ret != MBEDTLS_ERR_SSL_CLIENT_RECONNECT )
        {
            if( ret == MBEDTLS_ERR_SSL_UNEXPECTED_RECORD )
            {
                /* Skip unexpected record (but not whole datagram) */
                ssl->next_record_offset = ssl->in_msglen
                                        + mbedtls_ssl_hdr_len( ssl );

                MBEDTLS_SSL_DEBUG_MSG( 1, ( "discarding unexpected record "
                                            "(header)" ) );
            }
            else
            {
                /* Skip invalid record and the rest of the datagram */
                ssl->next_record_offset = 0;
                ssl->in_left = 0;

                MBEDTLS_SSL_DEBUG_MSG( 1, ( "discarding invalid record "
                                            "(header)" ) );
            }

            /* Get next record */
            goto read_record_header;
        }
#endif
        return( ret );
    }

    /*
     * Read and optionally decrypt the message contents
     */
    if( ( ret = mbedtls_ssl_fetch_input( ssl,
                                 mbedtls_ssl_hdr_len( ssl ) + ssl->in_msglen ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_fetch_input", ret );
        return( ret );
    }

    /* Done reading this record, get ready for the next one */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
        ssl->next_record_offset = ssl->in_msglen + mbedtls_ssl_hdr_len( ssl );
    else
#endif
        ssl->in_left = 0;

    if( ( ret = ssl_prepare_record_content( ssl ) ) != 0 )
    {
#if defined(MBEDTLS_SSL_PROTO_DTLS)
        if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
        {
            /* Silently discard invalid records */
            if( ret == MBEDTLS_ERR_SSL_INVALID_RECORD ||
                ret == MBEDTLS_ERR_SSL_INVALID_MAC )
            {
                /* Except when waiting for Finished as a bad mac here
                 * probably means something went wrong in the handshake
                 * (eg wrong psk used, mitm downgrade attempt, etc.) */
                if( ssl->state == MBEDTLS_SSL_CLIENT_FINISHED ||
                    ssl->state == MBEDTLS_SSL_SERVER_FINISHED )
                {
#if defined(MBEDTLS_SSL_ALL_ALERT_MESSAGES)
                    if( ret == MBEDTLS_ERR_SSL_INVALID_MAC )
                    {
                        mbedtls_ssl_send_alert_message( ssl,
                                MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                MBEDTLS_SSL_ALERT_MSG_BAD_RECORD_MAC );
                    }
#endif
                    return( ret );
                }

#if defined(MBEDTLS_SSL_DTLS_BADMAC_LIMIT)
                if( ssl->conf->badmac_limit != 0 &&
                    ++ssl->badmac_seen >= ssl->conf->badmac_limit )
                {
                    MBEDTLS_SSL_DEBUG_MSG( 1, ( "too many records with bad MAC" ) );
                    return( MBEDTLS_ERR_SSL_INVALID_MAC );
                }
#endif

                /* As above, invalid records cause
                 * dismissal of the whole datagram. */

                ssl->next_record_offset = 0;
                ssl->in_left = 0;

                MBEDTLS_SSL_DEBUG_MSG( 1, ( "discarding invalid record (mac)" ) );
                goto read_record_header;
            }

            return( ret );
        }
        else
#endif
        {
            /* Error out (and send alert) on invalid records */
#if defined(MBEDTLS_SSL_ALL_ALERT_MESSAGES)
            if( ret == MBEDTLS_ERR_SSL_INVALID_MAC )
            {
                mbedtls_ssl_send_alert_message( ssl,
                        MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                        MBEDTLS_SSL_ALERT_MSG_BAD_RECORD_MAC );
            }
#endif
            return( ret );
        }
    }

    /*
     * When we sent the last flight of the handshake, we MUST respond to a
     * retransmit of the peer's previous flight with a retransmit. (In
     * practice, only the Finished message will make it, other messages
     * including CCS use the old transform so they're dropped as invalid.)
     *
     * If the record we received is not a handshake message, however, it
     * means the peer received our last flight so we can clean up
     * handshake info.
     *
     * This check needs to be done before prepare_handshake() due to an edge
     * case: if the client immediately requests renegotiation, this
     * finishes the current handshake first, avoiding the new ClientHello
     * being mistaken for an ancient message in the current handshake.
     */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake != NULL &&
        ssl->state == MBEDTLS_SSL_HANDSHAKE_OVER )
    {
        if( ssl->in_msgtype == MBEDTLS_SSL_MSG_HANDSHAKE &&
                ssl->in_msg[0] == MBEDTLS_SSL_HS_FINISHED )
        {
            MBEDTLS_SSL_DEBUG_MSG( 2, ( "received retransmit of last flight" ) );

            if( ( ret = mbedtls_ssl_resend( ssl ) ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_resend", ret );
                return( ret );
            }

            return( MBEDTLS_ERR_SSL_WANT_READ );
        }
        else
        {
            ssl_handshake_wrapup_free_hs_transform( ssl );
        }
    }
#endif

    return( 0 );
}