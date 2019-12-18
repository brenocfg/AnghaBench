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

/* Variables and functions */
 int /*<<< orphan*/  cleanup_dead_labels () ; 
 int /*<<< orphan*/  cleanup_tree_cfg () ; 
 int /*<<< orphan*/  fold_cond_expr_cond () ; 
 int /*<<< orphan*/  group_case_labels () ; 

__attribute__((used)) static unsigned int
execute_cleanup_cfg_post_optimizing (void)
{
  fold_cond_expr_cond ();
  cleanup_tree_cfg ();
  cleanup_dead_labels ();
  group_case_labels ();
  return 0;
}