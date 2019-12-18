#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* cli_id; struct TYPE_10__* hostname; struct TYPE_10__* session; struct TYPE_10__* session_negotiate; struct TYPE_10__* transform_negotiate; struct TYPE_10__* handshake; struct TYPE_10__* transform; struct TYPE_10__* compress_buf; struct TYPE_10__* in_buf; struct TYPE_10__* out_buf; } ;
typedef  TYPE_1__ mbedtls_ssl_context ;

/* Variables and functions */
 int MBEDTLS_SSL_BUFFER_LEN ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  mbedtls_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_handshake_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_hw_record_finish (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_session_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_transform_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_1__*,int) ; 
 int strlen (TYPE_1__*) ; 

void mbedtls_ssl_free( mbedtls_ssl_context *ssl )
{
    if( ssl == NULL )
        return;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> free" ) );

    if( ssl->out_buf != NULL )
    {
        mbedtls_zeroize( ssl->out_buf, MBEDTLS_SSL_BUFFER_LEN );
        mbedtls_free( ssl->out_buf );
    }

    if( ssl->in_buf != NULL )
    {
        mbedtls_zeroize( ssl->in_buf, MBEDTLS_SSL_BUFFER_LEN );
        mbedtls_free( ssl->in_buf );
    }

#if defined(MBEDTLS_ZLIB_SUPPORT)
    if( ssl->compress_buf != NULL )
    {
        mbedtls_zeroize( ssl->compress_buf, MBEDTLS_SSL_BUFFER_LEN );
        mbedtls_free( ssl->compress_buf );
    }
#endif

    if( ssl->transform )
    {
        mbedtls_ssl_transform_free( ssl->transform );
        mbedtls_free( ssl->transform );
    }

    if( ssl->handshake )
    {
        mbedtls_ssl_handshake_free( ssl->handshake );
        mbedtls_ssl_transform_free( ssl->transform_negotiate );
        mbedtls_ssl_session_free( ssl->session_negotiate );

        mbedtls_free( ssl->handshake );
        mbedtls_free( ssl->transform_negotiate );
        mbedtls_free( ssl->session_negotiate );
    }

    if( ssl->session )
    {
        mbedtls_ssl_session_free( ssl->session );
        mbedtls_free( ssl->session );
    }

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    if( ssl->hostname != NULL )
    {
        mbedtls_zeroize( ssl->hostname, strlen( ssl->hostname ) );
        mbedtls_free( ssl->hostname );
    }
#endif

#if defined(MBEDTLS_SSL_HW_RECORD_ACCEL)
    if( mbedtls_ssl_hw_record_finish != NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "going for mbedtls_ssl_hw_record_finish()" ) );
        mbedtls_ssl_hw_record_finish( ssl );
    }
#endif

#if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY) && defined(MBEDTLS_SSL_SRV_C)
    mbedtls_free( ssl->cli_id );
#endif

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= free" ) );

    /* Actually clear after last debug message */
    mbedtls_zeroize( ssl, sizeof( mbedtls_ssl_context ) );
}