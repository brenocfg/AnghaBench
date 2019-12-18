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
struct dwarf_expr_context {scalar_t__ stack_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

void
dwarf_expr_pop (struct dwarf_expr_context *ctx)
{
  if (ctx->stack_len <= 0)
    error ("dwarf expression stack underflow");
  ctx->stack_len--;
}