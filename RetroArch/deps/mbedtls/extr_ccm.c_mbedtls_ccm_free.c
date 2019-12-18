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
struct TYPE_4__ {int /*<<< orphan*/  cipher_ctx; } ;
typedef  TYPE_1__ mbedtls_ccm_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_cipher_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_1__*,int) ; 

void mbedtls_ccm_free( mbedtls_ccm_context *ctx )
{
    mbedtls_cipher_free( &ctx->cipher_ctx );
    mbedtls_zeroize( ctx, sizeof( mbedtls_ccm_context ) );
}