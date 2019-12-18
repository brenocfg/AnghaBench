#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ keep_current_message; scalar_t__ in_msgtype; } ;
typedef  TYPE_1__ mbedtls_ssl_context ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_NON_FATAL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 scalar_t__ MBEDTLS_SSL_MSG_HANDSHAKE ; 
 int mbedtls_ssl_handle_message_type (TYPE_1__*) ; 
 int mbedtls_ssl_read_record_layer (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_update_handshake_status (TYPE_1__*) ; 

int mbedtls_ssl_read_record( mbedtls_ssl_context *ssl )
{
    int ret;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> read record" ) );

    if( ssl->keep_current_message == 0 )
    {
        do {

            if( ( ret = mbedtls_ssl_read_record_layer( ssl ) ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, ( "mbedtls_ssl_read_record_layer" ), ret );
                return( ret );
            }

            ret = mbedtls_ssl_handle_message_type( ssl );

        } while( MBEDTLS_ERR_SSL_NON_FATAL == ret );

        if( 0 != ret )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "mbedtls_ssl_read_record_layer" ), ret );
            return( ret );
        }

        if( ssl->in_msgtype == MBEDTLS_SSL_MSG_HANDSHAKE )
        {
            mbedtls_ssl_update_handshake_status( ssl );
        }
    }
    else
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= reuse previously read message" ) );
        ssl->keep_current_message = 0;
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= read record" ) );

    return( 0 );
}