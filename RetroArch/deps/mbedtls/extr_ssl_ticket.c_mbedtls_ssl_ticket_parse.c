#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ mbedtls_time_t ;
struct TYPE_9__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ mbedtls_ssl_ticket_key ;
struct TYPE_10__ {scalar_t__ ticket_lifetime; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * f_rng; } ;
typedef  TYPE_2__ mbedtls_ssl_ticket_context ;
struct TYPE_11__ {scalar_t__ start; } ;
typedef  TYPE_3__ mbedtls_ssl_session ;

/* Variables and functions */
 int MBEDTLS_ERR_CIPHER_AUTH_FAILED ; 
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 int MBEDTLS_ERR_SSL_INVALID_MAC ; 
 int MBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED ; 
 int MBEDTLS_ERR_THREADING_MUTEX_ERROR ; 
 int mbedtls_cipher_auth_decrypt (int /*<<< orphan*/ *,unsigned char*,int,unsigned char*,int,unsigned char*,size_t,unsigned char*,size_t*,unsigned char*,int) ; 
 int mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_time (int /*<<< orphan*/ *) ; 
 int ssl_load_session (TYPE_3__*,unsigned char*,size_t) ; 
 TYPE_1__* ssl_ticket_select_key (TYPE_2__*,unsigned char*) ; 
 int ssl_ticket_update_keys (TYPE_2__*) ; 

int mbedtls_ssl_ticket_parse( void *p_ticket,
                              mbedtls_ssl_session *session,
                              unsigned char *buf,
                              size_t len )
{
    int ret;
    mbedtls_ssl_ticket_context *ctx = p_ticket;
    mbedtls_ssl_ticket_key *key;
    unsigned char *key_name = buf;
    unsigned char *iv = buf + 4;
    unsigned char *enc_len_p = iv + 12;
    unsigned char *ticket = enc_len_p + 2;
    unsigned char *tag;
    size_t enc_len, clear_len;

    if( ctx == NULL || ctx->f_rng == NULL )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    /* See mbedtls_ssl_ticket_write() */
    if( len < 4 + 12 + 2 + 16 )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

#if defined(MBEDTLS_THREADING_C)
    if( ( ret = mbedtls_mutex_lock( &ctx->mutex ) ) != 0 )
        return( ret );
#endif

    if( ( ret = ssl_ticket_update_keys( ctx ) ) != 0 )
        goto cleanup;

    enc_len = ( enc_len_p[0] << 8 ) | enc_len_p[1];
    tag = ticket + enc_len;

    if( len != 4 + 12 + 2 + enc_len + 16 )
    {
        ret = MBEDTLS_ERR_SSL_BAD_INPUT_DATA;
        goto cleanup;
    }

    /* Select key */
    if( ( key = ssl_ticket_select_key( ctx, key_name ) ) == NULL )
    {
        /* We can't know for sure but this is a likely option unless we're
         * under attack - this is only informative anyway */
        ret = MBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED;
        goto cleanup;
    }

    /* Decrypt and authenticate */
    if( ( ret = mbedtls_cipher_auth_decrypt( &key->ctx, iv, 12,
                    key_name, 4 + 12 + 2, ticket, enc_len,
                    ticket, &clear_len, tag, 16 ) ) != 0 )
    {
        if( ret == MBEDTLS_ERR_CIPHER_AUTH_FAILED )
            ret = MBEDTLS_ERR_SSL_INVALID_MAC;

        goto cleanup;
    }
    if( clear_len != enc_len )
    {
        ret = MBEDTLS_ERR_SSL_INTERNAL_ERROR;
        goto cleanup;
    }

    /* Actually load session */
    if( ( ret = ssl_load_session( session, ticket, clear_len ) ) != 0 )
        goto cleanup;

#if defined(MBEDTLS_HAVE_TIME)
    {
        /* Check for expiration */
        mbedtls_time_t current_time = mbedtls_time( NULL );

        if( current_time < session->start ||
            (uint32_t)( current_time - session->start ) > ctx->ticket_lifetime )
        {
            ret = MBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED;
            goto cleanup;
        }
    }
#endif

cleanup:
#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &ctx->mutex ) != 0 )
        return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

    return( ret );
}