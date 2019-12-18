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
 void* BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 void* addressable_vars ; 
 int aliases_computed_p ; 
 void* call_clobbered_vars ; 
 void* default_defs ; 
 int /*<<< orphan*/  global_var ; 
 void* htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_alias_heapvars () ; 
 int /*<<< orphan*/  init_phinodes () ; 
 int /*<<< orphan*/  init_ssanames () ; 
 int /*<<< orphan*/  int_tree_map_eq ; 
 int /*<<< orphan*/  int_tree_map_hash ; 
 void* referenced_vars ; 

void
init_tree_ssa (void)
{
  referenced_vars = htab_create_ggc (20, int_tree_map_hash, 
				     int_tree_map_eq, NULL);
  default_defs = htab_create_ggc (20, int_tree_map_hash, int_tree_map_eq, NULL);
  call_clobbered_vars = BITMAP_ALLOC (NULL);
  addressable_vars = BITMAP_ALLOC (NULL);
  init_alias_heapvars ();
  init_ssanames ();
  init_phinodes ();
  global_var = NULL_TREE;
  aliases_computed_p = false;
}