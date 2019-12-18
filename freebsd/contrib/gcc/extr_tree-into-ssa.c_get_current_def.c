#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int /*<<< orphan*/  current_def; } ;
struct TYPE_3__ {int /*<<< orphan*/  current_def; } ;

/* Variables and functions */
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 TYPE_2__* get_ssa_name_ann (int /*<<< orphan*/ ) ; 
 TYPE_1__* var_ann (int /*<<< orphan*/ ) ; 

tree
get_current_def (tree var)
{
  if (TREE_CODE (var) == SSA_NAME)
    return get_ssa_name_ann (var)->current_def;
  else
    return var_ann (var)->current_def;
}