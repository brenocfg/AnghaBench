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
struct TYPE_3__ {scalar_t__ unprocessed_len; int /*<<< orphan*/ * cipher_info; } ;
typedef  TYPE_1__ mbedtls_cipher_context_t ;

/* Variables and functions */
 int MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA ; 

int mbedtls_cipher_reset( mbedtls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );

    ctx->unprocessed_len = 0;

    return( 0 );
}