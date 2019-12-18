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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  grow_expr (struct agent_expr*,int) ; 

__attribute__((used)) static void
generic_ext (struct agent_expr *x, enum agent_op op, int n)
{
  /* N must fit in a byte.  */
  if (n < 0 || n > 255)
    error ("GDB bug: ax-general.c (generic_ext): bit count out of range");
  /* That had better be enough range.  */
  if (sizeof (LONGEST) * 8 > 255)
    error ("GDB bug: ax-general.c (generic_ext): opcode has inadequate range");

  grow_expr (x, 2);
  x->buf[x->len++] = op;
  x->buf[x->len++] = n;
}