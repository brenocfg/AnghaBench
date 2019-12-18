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
struct TYPE_6__ {unsigned char* in_buf; unsigned char* out_buf; unsigned char* out_hdr; unsigned char* out_ctr; unsigned char* out_len; unsigned char* out_iv; unsigned char* out_msg; unsigned char* in_hdr; unsigned char* in_ctr; unsigned char* in_len; unsigned char* in_iv; unsigned char* in_msg; TYPE_2__ const* conf; } ;
typedef  TYPE_1__ mbedtls_ssl_context ;
struct TYPE_7__ {scalar_t__ transport; } ;
typedef  TYPE_2__ mbedtls_ssl_config ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_ALLOC_FAILED ; 
 size_t MBEDTLS_SSL_BUFFER_LEN ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 scalar_t__ mbedtls_calloc (int,size_t const) ; 
 int /*<<< orphan*/  mbedtls_free (unsigned char*) ; 
 int ssl_handshake_init (TYPE_1__*) ; 

int mbedtls_ssl_setup( mbedtls_ssl_context *ssl,
                       const mbedtls_ssl_config *conf )
{
    int ret;
    const size_t len = MBEDTLS_SSL_BUFFER_LEN;

    ssl->conf = conf;

    /*
     * Prepare base structures
     */
    if( ( ssl-> in_buf = (unsigned char*)mbedtls_calloc( 1, len ) ) == NULL ||
        ( ssl->out_buf = (unsigned char*)mbedtls_calloc( 1, len ) ) == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "alloc(%d bytes) failed", len ) );
        mbedtls_free( ssl->in_buf );
        ssl->in_buf = NULL;
        return( MBEDTLS_ERR_SSL_ALLOC_FAILED );
    }

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        ssl->out_hdr = ssl->out_buf;
        ssl->out_ctr = ssl->out_buf +  3;
        ssl->out_len = ssl->out_buf + 11;
        ssl->out_iv  = ssl->out_buf + 13;
        ssl->out_msg = ssl->out_buf + 13;

        ssl->in_hdr = ssl->in_buf;
        ssl->in_ctr = ssl->in_buf +  3;
        ssl->in_len = ssl->in_buf + 11;
        ssl->in_iv  = ssl->in_buf + 13;
        ssl->in_msg = ssl->in_buf + 13;
    }
    else
#endif
    {
        ssl->out_ctr = ssl->out_buf;
        ssl->out_hdr = ssl->out_buf +  8;
        ssl->out_len = ssl->out_buf + 11;
        ssl->out_iv  = ssl->out_buf + 13;
        ssl->out_msg = ssl->out_buf + 13;

        ssl->in_ctr = ssl->in_buf;
        ssl->in_hdr = ssl->in_buf +  8;
        ssl->in_len = ssl->in_buf + 11;
        ssl->in_iv  = ssl->in_buf + 13;
        ssl->in_msg = ssl->in_buf + 13;
    }

    if( ( ret = ssl_handshake_init( ssl ) ) != 0 )
        return( ret );

    return( 0 );
}