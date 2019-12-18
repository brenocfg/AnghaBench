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
struct ptr_info_def {int dummy; } ;

/* Variables and functions */
 struct ptr_info_def* SSA_NAME_PTR_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  duplicate_ssa_name_ptr_info (int /*<<< orphan*/ ,struct ptr_info_def*) ; 
 int /*<<< orphan*/  make_ssa_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
duplicate_ssa_name (tree name, tree stmt)
{
  tree new_name = make_ssa_name (SSA_NAME_VAR (name), stmt);
  struct ptr_info_def *old_ptr_info = SSA_NAME_PTR_INFO (name);

  if (old_ptr_info)
    duplicate_ssa_name_ptr_info (new_name, old_ptr_info);

  return new_name;
}