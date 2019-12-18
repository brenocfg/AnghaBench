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
 int /*<<< orphan*/  aop_lsh ; 
 int /*<<< orphan*/  aop_rsh_unsigned ; 
 int /*<<< orphan*/  ax_const_l (struct agent_expr*,int) ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_left_shift (struct agent_expr *ax, int distance)
{
  if (distance > 0)
    {
      ax_const_l (ax, distance);
      ax_simple (ax, aop_lsh);
    }
  else if (distance < 0)
    {
      ax_const_l (ax, -distance);
      ax_simple (ax, aop_rsh_unsigned);
    }
}