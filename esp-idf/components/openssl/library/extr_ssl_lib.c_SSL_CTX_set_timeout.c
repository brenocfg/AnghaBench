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
struct TYPE_4__ {long session_timeout; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT1 (TYPE_1__*) ; 

long SSL_CTX_set_timeout(SSL_CTX *ctx, long t)
{
    long l;

    SSL_ASSERT1(ctx);

    l = ctx->session_timeout;
    ctx->session_timeout = t;

    return l;
}