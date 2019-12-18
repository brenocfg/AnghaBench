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
struct agent_expr {int* buf; size_t len; } ;
typedef  int reg ;

/* Variables and functions */
 int aop_reg ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  grow_expr (struct agent_expr*,int) ; 

void
ax_reg (struct agent_expr *x, int reg)
{
  /* Make sure the register number is in range.  */
  if (reg < 0 || reg > 0xffff)
    error ("GDB bug: ax-general.c (ax_reg): register number out of range");
  grow_expr (x, 3);
  x->buf[x->len] = aop_reg;
  x->buf[x->len + 1] = (reg >> 8) & 0xff;
  x->buf[x->len + 2] = (reg) & 0xff;
  x->len += 3;
}