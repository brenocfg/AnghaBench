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
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  basic_block ; 
 int /*<<< orphan*/  bb_in_list ; 
 int /*<<< orphan*/ * cfg_blocks ; 
 int /*<<< orphan*/  executable_blocks ; 
 int /*<<< orphan*/  gc ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/ * interesting_ssa_edges ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/ * varying_ssa_edges ; 

__attribute__((used)) static void
ssa_prop_fini (void)
{
  VEC_free (tree, gc, interesting_ssa_edges);
  VEC_free (tree, gc, varying_ssa_edges);
  VEC_free (basic_block, heap, cfg_blocks);
  cfg_blocks = NULL;
  sbitmap_free (bb_in_list);
  sbitmap_free (executable_blocks);
}