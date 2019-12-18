#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/  (* expand_decl ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_HARD_REGISTER (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_HAS_VALUE_EXPR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_RTL_SET_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  add_stack_var (int /*<<< orphan*/ ) ; 
 scalar_t__ defer_stack_allocation (int /*<<< orphan*/ ,int) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  expand_one_error_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_one_hard_reg_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_one_register_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_one_stack_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_one_static_var (int /*<<< orphan*/ ) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ use_register_for_decl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_one_var (tree var, bool toplevel)
{
  if (TREE_CODE (var) != VAR_DECL)
    lang_hooks.expand_decl (var);
  else if (DECL_EXTERNAL (var))
    ;
  else if (DECL_HAS_VALUE_EXPR_P (var))
    ;
  else if (TREE_STATIC (var))
    expand_one_static_var (var);
  else if (DECL_RTL_SET_P (var))
    ;
  else if (TREE_TYPE (var) == error_mark_node)
    expand_one_error_var (var);
  else if (DECL_HARD_REGISTER (var))
    expand_one_hard_reg_var (var);
  else if (use_register_for_decl (var))
    expand_one_register_var (var);
  else if (defer_stack_allocation (var, toplevel))
    add_stack_var (var);
  else
    expand_one_stack_var (var);
}