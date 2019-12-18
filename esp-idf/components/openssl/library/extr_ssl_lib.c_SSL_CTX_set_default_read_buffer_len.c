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
struct TYPE_4__ {size_t read_buffer_len; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT3 (TYPE_1__*) ; 

void SSL_CTX_set_default_read_buffer_len(SSL_CTX *ctx, size_t len)
{
    SSL_ASSERT3(ctx);

    ctx->read_buffer_len = len;
}