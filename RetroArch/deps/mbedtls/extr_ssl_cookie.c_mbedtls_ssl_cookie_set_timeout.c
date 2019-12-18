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
struct TYPE_3__ {unsigned long timeout; } ;
typedef  TYPE_1__ mbedtls_ssl_cookie_ctx ;

/* Variables and functions */

void mbedtls_ssl_cookie_set_timeout( mbedtls_ssl_cookie_ctx *ctx, unsigned long delay )
{
    ctx->timeout = delay;
}