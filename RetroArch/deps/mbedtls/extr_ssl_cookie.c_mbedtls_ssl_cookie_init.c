#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  timeout; scalar_t__ serial; int /*<<< orphan*/  hmac_ctx; } ;
typedef  TYPE_1__ mbedtls_ssl_cookie_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_SSL_COOKIE_TIMEOUT ; 
 int /*<<< orphan*/  mbedtls_md_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mutex_init (int /*<<< orphan*/ *) ; 

void mbedtls_ssl_cookie_init( mbedtls_ssl_cookie_ctx *ctx )
{
    mbedtls_md_init( &ctx->hmac_ctx );
#if !defined(MBEDTLS_HAVE_TIME)
    ctx->serial = 0;
#endif
    ctx->timeout = MBEDTLS_SSL_COOKIE_TIMEOUT;

#if defined(MBEDTLS_THREADING_C)
    mbedtls_mutex_init( &ctx->mutex );
#endif
}