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

/* Variables and functions */
 int /*<<< orphan*/  aop_add ; 
 int /*<<< orphan*/  aop_sub ; 
 int /*<<< orphan*/  ax_const_l (struct agent_expr*,int) ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_offset (struct agent_expr *ax, int offset)
{
  /* It would suffice to simply push the offset and add it, but this
     makes it easier to read positive and negative offsets in the
     bytecode.  */
  if (offset > 0)
    {
      ax_const_l (ax, offset);
      ax_simple (ax, aop_add);
    }
  else if (offset < 0)
    {
      ax_const_l (ax, -offset);
      ax_simple (ax, aop_sub);
    }
}