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
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * control_dependence_map ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap ; 
 int last_basic_block ; 
 int /*<<< orphan*/  last_stmt_necessary ; 
 int /*<<< orphan*/  processed ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  visited_control_parents ; 
 int /*<<< orphan*/  worklist ; 

__attribute__((used)) static void
tree_dce_done (bool aggressive)
{
  if (aggressive)
    {
      int i;

      for (i = 0; i < last_basic_block; ++i)
	BITMAP_FREE (control_dependence_map[i]);
      free (control_dependence_map);

      sbitmap_free (visited_control_parents);
      sbitmap_free (last_stmt_necessary);
    }

  sbitmap_free (processed);

  VEC_free (tree, heap, worklist);
}