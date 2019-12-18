#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  md_ctx; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ mbedtls_hmac_drbg_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_md_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mutex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_1__*,int) ; 

void mbedtls_hmac_drbg_free( mbedtls_hmac_drbg_context *ctx )
{
    if( ctx == NULL )
        return;

#if defined(MBEDTLS_THREADING_C)
    mbedtls_mutex_free( &ctx->mutex );
#endif
    mbedtls_md_free( &ctx->md_ctx );
    mbedtls_zeroize( ctx, sizeof( mbedtls_hmac_drbg_context ) );
}