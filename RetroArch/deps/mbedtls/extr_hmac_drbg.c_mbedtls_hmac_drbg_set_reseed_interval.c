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
struct TYPE_3__ {int reseed_interval; } ;
typedef  TYPE_1__ mbedtls_hmac_drbg_context ;

/* Variables and functions */

void mbedtls_hmac_drbg_set_reseed_interval( mbedtls_hmac_drbg_context *ctx, int interval )
{
    ctx->reseed_interval = interval;
}