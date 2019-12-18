#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* f_send ) (int /*<<< orphan*/ ,unsigned char*,int) ;int out_left; int out_msglen; scalar_t__* out_ctr; int /*<<< orphan*/  p_bio; int /*<<< orphan*/  out_hdr; } ;
typedef  TYPE_1__ mbedtls_ssl_context ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_SSL_COUNTER_WRAPPING ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 int mbedtls_ssl_hdr_len (TYPE_1__*) ; 
 unsigned char ssl_ep_len (TYPE_1__*) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 

int mbedtls_ssl_flush_output( mbedtls_ssl_context *ssl )
{
    int ret;
    unsigned char *buf, i;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> flush output" ) );

    if( ssl->f_send == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "Bad usage of mbedtls_ssl_set_bio() "
                            "or mbedtls_ssl_set_bio()" ) );
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );
    }

    /* Avoid incrementing counter if data is flushed */
    if( ssl->out_left == 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= flush output" ) );
        return( 0 );
    }

    while( ssl->out_left > 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "message length: %d, out_left: %d",
                       mbedtls_ssl_hdr_len( ssl ) + ssl->out_msglen, ssl->out_left ) );

        buf = ssl->out_hdr + mbedtls_ssl_hdr_len( ssl ) +
              ssl->out_msglen - ssl->out_left;
        ret = ssl->f_send( ssl->p_bio, buf, ssl->out_left );

        MBEDTLS_SSL_DEBUG_RET( 2, "ssl->f_send", ret );

        if( ret <= 0 )
            return( ret );

        ssl->out_left -= ret;
    }

    for( i = 8; i > ssl_ep_len( ssl ); i-- )
        if( ++ssl->out_ctr[i - 1] != 0 )
            break;

    /* The loop goes to its end iff the counter is wrapping */
    if( i == ssl_ep_len( ssl ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "outgoing message counter would wrap" ) );
        return( MBEDTLS_ERR_SSL_COUNTER_WRAPPING );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= flush output" ) );

    return( 0 );
}