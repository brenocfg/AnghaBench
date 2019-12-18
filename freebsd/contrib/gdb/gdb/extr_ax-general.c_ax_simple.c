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
typedef  enum agent_op { ____Placeholder_agent_op } agent_op ;

/* Variables and functions */
 int /*<<< orphan*/  grow_expr (struct agent_expr*,int) ; 

void
ax_simple (struct agent_expr *x, enum agent_op op)
{
  grow_expr (x, 1);
  x->buf[x->len++] = op;
}