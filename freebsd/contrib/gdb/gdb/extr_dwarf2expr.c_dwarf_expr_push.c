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
struct dwarf_expr_context {int /*<<< orphan*/  stack_len; int /*<<< orphan*/ * stack; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf_expr_grow_stack (struct dwarf_expr_context*,int) ; 

void
dwarf_expr_push (struct dwarf_expr_context *ctx, CORE_ADDR value)
{
  dwarf_expr_grow_stack (ctx, 1);
  ctx->stack[ctx->stack_len++] = value;
}