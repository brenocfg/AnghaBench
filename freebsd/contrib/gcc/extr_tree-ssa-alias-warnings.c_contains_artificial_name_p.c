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

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_artificial_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ssa_base (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
contains_artificial_name_p (tree var)
{
  if (TREE_CODE (var) == SSA_NAME)
    return contains_artificial_name_p (get_ssa_base (var));

  return find_first_artificial_name (var) != NULL_TREE;
}