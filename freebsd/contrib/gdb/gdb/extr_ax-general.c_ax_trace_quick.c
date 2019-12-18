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
struct agent_expr {int* buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int aop_trace_quick ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  grow_expr (struct agent_expr*,int) ; 

void
ax_trace_quick (struct agent_expr *x, int n)
{
  /* N must fit in a byte.  */
  if (n < 0 || n > 255)
    error ("GDB bug: ax-general.c (ax_trace_quick): size out of range for trace_quick");

  grow_expr (x, 2);
  x->buf[x->len++] = aop_trace_quick;
  x->buf[x->len++] = n;
}