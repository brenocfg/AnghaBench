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
struct TYPE_3__ {size_t entropy_len; } ;
typedef  TYPE_1__ mbedtls_hmac_drbg_context ;

/* Variables and functions */

void mbedtls_hmac_drbg_set_entropy_len( mbedtls_hmac_drbg_context *ctx, size_t len )
{
    ctx->entropy_len = len;
}