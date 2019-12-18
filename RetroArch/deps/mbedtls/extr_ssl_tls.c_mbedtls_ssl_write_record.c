#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {size_t out_msglen; scalar_t__ out_msgtype; int* out_msg; unsigned char* out_hdr; unsigned char* out_len; scalar_t__ out_left; int /*<<< orphan*/ * transform_out; TYPE_3__* conf; int /*<<< orphan*/  minor_ver; int /*<<< orphan*/  major_ver; TYPE_2__* session_out; TYPE_1__* handshake; } ;
typedef  TYPE_4__ mbedtls_ssl_context ;
struct TYPE_15__ {scalar_t__ transport; } ;
struct TYPE_14__ {scalar_t__ compression; } ;
struct TYPE_13__ {scalar_t__ retransmit_state; int out_msg_seq; int /*<<< orphan*/  (* update_checksum ) (TYPE_4__*,int*,size_t) ;} ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_HW_ACCEL_FAILED ; 
 int MBEDTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 scalar_t__ MBEDTLS_SSL_COMPRESS_DEFLATE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_BUF (int,char*,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 int MBEDTLS_SSL_HS_HELLO_REQUEST ; 
 scalar_t__ MBEDTLS_SSL_MSG_CHANGE_CIPHER_SPEC ; 
 scalar_t__ MBEDTLS_SSL_MSG_HANDSHAKE ; 
 scalar_t__ MBEDTLS_SSL_RETRANS_SENDING ; 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 int mbedtls_ssl_flush_output (TYPE_4__*) ; 
 scalar_t__ mbedtls_ssl_hdr_len (TYPE_4__*) ; 
 int mbedtls_ssl_hw_record_write (TYPE_4__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_write_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int ssl_compress_buf (TYPE_4__*) ; 
 int ssl_encrypt_buf (TYPE_4__*) ; 
 int ssl_flight_append (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int*,size_t) ; 

int mbedtls_ssl_write_record( mbedtls_ssl_context *ssl )
{
    int ret, done = 0, out_msg_type;
    size_t len = ssl->out_msglen;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write record" ) );

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake != NULL &&
        ssl->handshake->retransmit_state == MBEDTLS_SSL_RETRANS_SENDING )
    {
        ; /* Skip special handshake treatment when resending */
    }
    else
#endif
    if( ssl->out_msgtype == MBEDTLS_SSL_MSG_HANDSHAKE )
    {
        out_msg_type = ssl->out_msg[0];

        if( out_msg_type != MBEDTLS_SSL_HS_HELLO_REQUEST &&
            ssl->handshake == NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }

        ssl->out_msg[1] = (unsigned char)( ( len - 4 ) >> 16 );
        ssl->out_msg[2] = (unsigned char)( ( len - 4 ) >>  8 );
        ssl->out_msg[3] = (unsigned char)( ( len - 4 )       );

        /*
         * DTLS has additional fields in the Handshake layer,
         * between the length field and the actual payload:
         *      uint16 message_seq;
         *      uint24 fragment_offset;
         *      uint24 fragment_length;
         */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
        if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
        {
            /* Make room for the additional DTLS fields */
            memmove( ssl->out_msg + 12, ssl->out_msg + 4, len - 4 );
            ssl->out_msglen += 8;
            len += 8;

            /* Write message_seq and update it, except for HelloRequest */
            if( out_msg_type != MBEDTLS_SSL_HS_HELLO_REQUEST )
            {
                ssl->out_msg[4] = ( ssl->handshake->out_msg_seq >> 8 ) & 0xFF;
                ssl->out_msg[5] = ( ssl->handshake->out_msg_seq      ) & 0xFF;
                ++( ssl->handshake->out_msg_seq );
            }
            else
            {
                ssl->out_msg[4] = 0;
                ssl->out_msg[5] = 0;
            }

            /* We don't fragment, so frag_offset = 0 and frag_len = len */
            memset( ssl->out_msg + 6, 0x00, 3 );
            memcpy( ssl->out_msg + 9, ssl->out_msg + 1, 3 );
        }
#endif /* MBEDTLS_SSL_PROTO_DTLS */

        if( out_msg_type != MBEDTLS_SSL_HS_HELLO_REQUEST )
            ssl->handshake->update_checksum( ssl, ssl->out_msg, len );
    }

    /* Save handshake and CCS messages for resending */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake != NULL &&
        ssl->handshake->retransmit_state != MBEDTLS_SSL_RETRANS_SENDING &&
        ( ssl->out_msgtype == MBEDTLS_SSL_MSG_CHANGE_CIPHER_SPEC ||
          ssl->out_msgtype == MBEDTLS_SSL_MSG_HANDSHAKE ) )
    {
        if( ( ret = ssl_flight_append( ssl ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "ssl_flight_append", ret );
            return( ret );
        }
    }
#endif

#if defined(MBEDTLS_ZLIB_SUPPORT)
    if( ssl->transform_out != NULL &&
        ssl->session_out->compression == MBEDTLS_SSL_COMPRESS_DEFLATE )
    {
        if( ( ret = ssl_compress_buf( ssl ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "ssl_compress_buf", ret );
            return( ret );
        }

        len = ssl->out_msglen;
    }
#endif /*MBEDTLS_ZLIB_SUPPORT */

#if defined(MBEDTLS_SSL_HW_RECORD_ACCEL)
    if( mbedtls_ssl_hw_record_write != NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "going for mbedtls_ssl_hw_record_write()" ) );

        ret = mbedtls_ssl_hw_record_write( ssl );
        if( ret != 0 && ret != MBEDTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_hw_record_write", ret );
            return( MBEDTLS_ERR_SSL_HW_ACCEL_FAILED );
        }

        if( ret == 0 )
            done = 1;
    }
#endif /* MBEDTLS_SSL_HW_RECORD_ACCEL */
    if( !done )
    {
        ssl->out_hdr[0] = (unsigned char) ssl->out_msgtype;
        mbedtls_ssl_write_version( ssl->major_ver, ssl->minor_ver,
                           ssl->conf->transport, ssl->out_hdr + 1 );

        ssl->out_len[0] = (unsigned char)( len >> 8 );
        ssl->out_len[1] = (unsigned char)( len      );

        if( ssl->transform_out != NULL )
        {
            if( ( ret = ssl_encrypt_buf( ssl ) ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "ssl_encrypt_buf", ret );
                return( ret );
            }

            len = ssl->out_msglen;
            ssl->out_len[0] = (unsigned char)( len >> 8 );
            ssl->out_len[1] = (unsigned char)( len      );
        }

        ssl->out_left = mbedtls_ssl_hdr_len( ssl ) + ssl->out_msglen;

        MBEDTLS_SSL_DEBUG_MSG( 3, ( "output record: msgtype = %d, "
                            "version = [%d:%d], msglen = %d",
                       ssl->out_hdr[0], ssl->out_hdr[1], ssl->out_hdr[2],
                     ( ssl->out_len[0] << 8 ) | ssl->out_len[1] ) );

        MBEDTLS_SSL_DEBUG_BUF( 4, "output record sent to network",
                       ssl->out_hdr, mbedtls_ssl_hdr_len( ssl ) + ssl->out_msglen );
    }

    if( ( ret = mbedtls_ssl_flush_output( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_flush_output", ret );
        return( ret );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write record" ) );

    return( 0 );
}