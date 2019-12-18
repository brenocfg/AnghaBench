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
struct dom_walk_data {int /*<<< orphan*/  before_dom_children_before_stmts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_BLOCK_PTR ; 
 int /*<<< orphan*/  determine_invariantness_stmt ; 
 int /*<<< orphan*/  fini_walk_dominator_tree (struct dom_walk_data*) ; 
 int /*<<< orphan*/  init_walk_dominator_tree (struct dom_walk_data*) ; 
 int /*<<< orphan*/  memset (struct dom_walk_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walk_dominator_tree (struct dom_walk_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
determine_invariantness (void)
{
  struct dom_walk_data walk_data;

  memset (&walk_data, 0, sizeof (struct dom_walk_data));
  walk_data.before_dom_children_before_stmts = determine_invariantness_stmt;

  init_walk_dominator_tree (&walk_data);
  walk_dominator_tree (&walk_data, ENTRY_BLOCK_PTR);
  fini_walk_dominator_tree (&walk_data);
}