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
struct agent_expr {int dummy; } ;
typedef  enum agent_op { ____Placeholder_agent_op } agent_op ;
typedef  int LONGEST ;

/* Variables and functions */
#define  aop_const16 131 
#define  aop_const32 130 
#define  aop_const64 129 
#define  aop_const8 128 
 int /*<<< orphan*/  append_const (struct agent_expr*,int,int) ; 
 int /*<<< orphan*/  ax_ext (struct agent_expr*,int) ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int) ; 

void
ax_const_l (struct agent_expr *x, LONGEST l)
{
  static enum agent_op ops[]
  =
  {aop_const8, aop_const16, aop_const32, aop_const64};
  int size;
  int op;

  /* How big is the number?  'op' keeps track of which opcode to use.
     Notice that we don't really care whether the original number was
     signed or unsigned; we always reproduce the value exactly, and
     use the shortest representation.  */
  for (op = 0, size = 8; size < 64; size *= 2, op++)
    if (-((LONGEST) 1 << size) <= l && l < ((LONGEST) 1 << size))
      break;

  /* Emit the right opcode... */
  ax_simple (x, ops[op]);

  /* Emit the low SIZE bytes as an unsigned number.  We know that
     sign-extending this will yield l.  */
  append_const (x, l, size / 8);

  /* Now, if it was negative, and not full-sized, sign-extend it.  */
  if (l < 0 && size < 64)
    ax_ext (x, size);
}