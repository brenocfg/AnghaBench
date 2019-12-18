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
 int /*<<< orphan*/  aop_ext ; 
 int /*<<< orphan*/  generic_ext (struct agent_expr*,int /*<<< orphan*/ ,int) ; 

void
ax_ext (struct agent_expr *x, int n)
{
  generic_ext (x, aop_ext, n);
}