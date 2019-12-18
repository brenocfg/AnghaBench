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
typedef  int /*<<< orphan*/  tree ;
struct assign_parm_data_all {int /*<<< orphan*/  reg_parm_stack_space; int /*<<< orphan*/  args_so_far; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CUMULATIVE_ARGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INIT_CUMULATIVE_INCOMING_ARGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  REG_PARM_STACK_SPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  memset (struct assign_parm_data_all*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
assign_parms_initialize_all (struct assign_parm_data_all *all)
{
  tree fntype;

  memset (all, 0, sizeof (*all));

  fntype = TREE_TYPE (current_function_decl);

#ifdef INIT_CUMULATIVE_INCOMING_ARGS
  INIT_CUMULATIVE_INCOMING_ARGS (all->args_so_far, fntype, NULL_RTX);
#else
  INIT_CUMULATIVE_ARGS (all->args_so_far, fntype, NULL_RTX,
			current_function_decl, -1);
#endif

#ifdef REG_PARM_STACK_SPACE
  all->reg_parm_stack_space = REG_PARM_STACK_SPACE (current_function_decl);
#endif
}