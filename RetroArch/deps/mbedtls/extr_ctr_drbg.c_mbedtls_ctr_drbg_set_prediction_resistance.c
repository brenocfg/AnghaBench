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
struct TYPE_3__ {int prediction_resistance; } ;
typedef  TYPE_1__ mbedtls_ctr_drbg_context ;

/* Variables and functions */

void mbedtls_ctr_drbg_set_prediction_resistance( mbedtls_ctr_drbg_context *ctx, int resistance )
{
    ctx->prediction_resistance = resistance;
}