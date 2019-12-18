#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dwarf_expr_context {size_t stack_len; size_t stack_allocated; int /*<<< orphan*/  stack; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  xrealloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
dwarf_expr_grow_stack (struct dwarf_expr_context *ctx, size_t need)
{
  if (ctx->stack_len + need > ctx->stack_allocated)
    {
      size_t newlen = ctx->stack_len + need + 10;
      ctx->stack = xrealloc (ctx->stack,
			     newlen * sizeof (CORE_ADDR));
      ctx->stack_allocated = newlen;
    }
}