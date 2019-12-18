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
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ heapvar_for_stmt ; 
 scalar_t__ htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonlocal_all ; 
 int /*<<< orphan*/  tree_map_eq ; 
 int /*<<< orphan*/  tree_map_hash ; 

void
init_alias_heapvars (void)
{
  if (!heapvar_for_stmt)
    heapvar_for_stmt = htab_create_ggc (11, tree_map_hash, tree_map_eq,
					NULL);
  nonlocal_all = NULL_TREE;
}