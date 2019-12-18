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
 int /*<<< orphan*/  htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shadowed_var_for_decl ; 
 int /*<<< orphan*/  tree_map_eq ; 
 int /*<<< orphan*/  tree_map_hash ; 

void
init_shadowed_var_for_decl (void)
{
  shadowed_var_for_decl = htab_create_ggc (512, tree_map_hash,
					   tree_map_eq, 0);
}