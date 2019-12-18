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
typedef  int /*<<< orphan*/  ref_hmac ;
struct TYPE_2__ {unsigned long serial; unsigned long timeout; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hmac_ctx; } ;
typedef  TYPE_1__ mbedtls_ssl_cookie_ctx ;

/* Variables and functions */
 int COOKIE_HMAC_LEN ; 
 size_t COOKIE_LEN ; 
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 int MBEDTLS_ERR_THREADING_MUTEX_ERROR ; 
 int mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_ssl_safer_memcmp (unsigned char const*,unsigned char*,int) ; 
 scalar_t__ mbedtls_time (int /*<<< orphan*/ *) ; 
 scalar_t__ ssl_cookie_hmac (int /*<<< orphan*/ *,unsigned char const*,unsigned char**,unsigned char*,unsigned char const*,size_t) ; 

int mbedtls_ssl_cookie_check( void *p_ctx,
                      const unsigned char *cookie, size_t cookie_len,
                      const unsigned char *cli_id, size_t cli_id_len )
{
    unsigned char ref_hmac[COOKIE_HMAC_LEN];
    int ret = 0;
    unsigned char *p = ref_hmac;
    mbedtls_ssl_cookie_ctx *ctx = (mbedtls_ssl_cookie_ctx *) p_ctx;
    unsigned long cur_time, cookie_time;

    if( ctx == NULL || cli_id == NULL )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    if( cookie_len != COOKIE_LEN )
        return( -1 );

#if defined(MBEDTLS_THREADING_C)
    if( ( ret = mbedtls_mutex_lock( &ctx->mutex ) ) != 0 )
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR + ret );
#endif

    if( ssl_cookie_hmac( &ctx->hmac_ctx, cookie,
                         &p, p + sizeof( ref_hmac ),
                         cli_id, cli_id_len ) != 0 )
        ret = -1;

#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &ctx->mutex ) != 0 )
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR +
                MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

    if( ret != 0 )
        return( ret );

    if( mbedtls_ssl_safer_memcmp( cookie + 4, ref_hmac, sizeof( ref_hmac ) ) != 0 )
        return( -1 );

#if defined(MBEDTLS_HAVE_TIME)
    cur_time = (unsigned long) mbedtls_time( NULL );
#else
    cur_time = ctx->serial;
#endif

    cookie_time = ( (unsigned long) cookie[0] << 24 ) |
                  ( (unsigned long) cookie[1] << 16 ) |
                  ( (unsigned long) cookie[2] <<  8 ) |
                  ( (unsigned long) cookie[3]       );

    if( ctx->timeout != 0 && cur_time - cookie_time > ctx->timeout )
        return( -1 );

    return( 0 );
}