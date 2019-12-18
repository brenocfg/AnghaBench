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
struct fmt_data {int /*<<< orphan*/  loop; int /*<<< orphan*/  orig_loop; } ;

/* Variables and functions */
 scalar_t__ ARRAY_REF ; 
 scalar_t__ IS_EMPTY_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref_element_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref_low_bound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_move_till_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
force_move_till (tree ref, tree *index, void *data)
{
  tree stmt;
  struct fmt_data *fmt_data = data;

  if (TREE_CODE (ref) == ARRAY_REF)
    {
      tree step = array_ref_element_size (ref);
      tree lbound = array_ref_low_bound (ref);

      force_move_till_expr (step, fmt_data->orig_loop, fmt_data->loop);
      force_move_till_expr (lbound, fmt_data->orig_loop, fmt_data->loop);
    }

  if (TREE_CODE (*index) != SSA_NAME)
    return true;

  stmt = SSA_NAME_DEF_STMT (*index);
  if (IS_EMPTY_STMT (stmt))
    return true;

  set_level (stmt, fmt_data->orig_loop, fmt_data->loop);

  return true;
}