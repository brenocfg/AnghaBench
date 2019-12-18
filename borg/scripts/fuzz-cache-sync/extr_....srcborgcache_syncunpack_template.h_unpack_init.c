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
struct TYPE_3__ {int /*<<< orphan*/  user; scalar_t__ top; scalar_t__ trail; int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ unpack_context ;

/* Variables and functions */
 int /*<<< orphan*/  CS_HEADER ; 
 int /*<<< orphan*/  unpack_init_user_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void unpack_init(unpack_context* ctx)
{
    ctx->cs = CS_HEADER;
    ctx->trail = 0;
    ctx->top = 0;
    unpack_init_user_state(&ctx->user);
}