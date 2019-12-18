#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  out_buf; int /*<<< orphan*/  p_bio; int /*<<< orphan*/  (* f_send ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  in_left; int /*<<< orphan*/  in_buf; int /*<<< orphan*/  cli_id_len; int /*<<< orphan*/  cli_id; TYPE_1__* conf; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_5__ {int /*<<< orphan*/  p_cookie; int /*<<< orphan*/  f_cookie_check; int /*<<< orphan*/  f_cookie_write; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_CLIENT_RECONNECT ; 
 int MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_MAX_CONTENT_LEN ; 
 int ssl_check_dtls_clihlo_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int ssl_session_reset_int (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int ssl_handle_possible_reconnect( mbedtls_ssl_context *ssl )
{
    int ret;
    size_t len;

    ret = ssl_check_dtls_clihlo_cookie(
            ssl->conf->f_cookie_write,
            ssl->conf->f_cookie_check,
            ssl->conf->p_cookie,
            ssl->cli_id, ssl->cli_id_len,
            ssl->in_buf, ssl->in_left,
            ssl->out_buf, MBEDTLS_SSL_MAX_CONTENT_LEN, &len );

    MBEDTLS_SSL_DEBUG_RET( 2, "ssl_check_dtls_clihlo_cookie", ret );

    if( ret == MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED )
    {
        /* Don't check write errors as we can't do anything here.
         * If the error is permanent we'll catch it later,
         * if it's not, then hopefully it'll work next time. */
        (void) ssl->f_send( ssl->p_bio, ssl->out_buf, len );

        return( MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED );
    }

    if( ret == 0 )
    {
        /* Got a valid cookie, partially reset context */
        if( ( ret = ssl_session_reset_int( ssl, 1 ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "reset", ret );
            return( ret );
        }

        return( MBEDTLS_ERR_SSL_CLIENT_RECONNECT );
    }

    return( ret );
}