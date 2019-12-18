#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hmac_ctx; int /*<<< orphan*/  serial; } ;
typedef  TYPE_1__ mbedtls_ssl_cookie_ctx ;

/* Variables and functions */
 size_t COOKIE_LEN ; 
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 int MBEDTLS_ERR_THREADING_MUTEX_ERROR ; 
 int mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_time (int /*<<< orphan*/ *) ; 
 int ssl_cookie_hmac (int /*<<< orphan*/ *,unsigned char*,unsigned char**,unsigned char*,unsigned char const*,size_t) ; 

int mbedtls_ssl_cookie_write( void *p_ctx,
                      unsigned char **p, unsigned char *end,
                      const unsigned char *cli_id, size_t cli_id_len )
{
    int ret;
    mbedtls_ssl_cookie_ctx *ctx = (mbedtls_ssl_cookie_ctx *) p_ctx;
    unsigned long t;

    if( ctx == NULL || cli_id == NULL )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    if( (size_t)( end - *p ) < COOKIE_LEN )
        return( MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL );

#if defined(MBEDTLS_HAVE_TIME)
    t = (unsigned long) mbedtls_time( NULL );
#else
    t = ctx->serial++;
#endif

    (*p)[0] = (unsigned char)( t >> 24 );
    (*p)[1] = (unsigned char)( t >> 16 );
    (*p)[2] = (unsigned char)( t >>  8 );
    (*p)[3] = (unsigned char)( t       );
    *p += 4;

#if defined(MBEDTLS_THREADING_C)
    if( ( ret = mbedtls_mutex_lock( &ctx->mutex ) ) != 0 )
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR + ret );
#endif

    ret = ssl_cookie_hmac( &ctx->hmac_ctx, *p - 4,
                           p, end, cli_id, cli_id_len );

#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &ctx->mutex ) != 0 )
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR +
                MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

    return( ret );
}