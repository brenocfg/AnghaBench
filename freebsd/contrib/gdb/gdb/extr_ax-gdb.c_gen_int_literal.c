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
struct type {int dummy; } ;
struct axs_value {struct type* type; int /*<<< orphan*/  kind; } ;
struct agent_expr {int dummy; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  ax_const_l (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axs_rvalue ; 

__attribute__((used)) static void
gen_int_literal (struct agent_expr *ax, struct axs_value *value, LONGEST k,
		 struct type *type)
{
  ax_const_l (ax, k);
  value->kind = axs_rvalue;
  value->type = type;
}