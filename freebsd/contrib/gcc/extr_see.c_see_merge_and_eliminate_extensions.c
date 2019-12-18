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
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int last_bb ; 
 scalar_t__* see_bb_splay_ar ; 
 int /*<<< orphan*/  see_handle_extensions_for_one_ref ; 
 int /*<<< orphan*/  splay_tree_foreach (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
see_merge_and_eliminate_extensions (void)
{
  int i = 0;

  if (dump_file)
    fprintf (dump_file,
      "* Phase 2: Merge and eliminate locally redundant extensions.  *\n");

  /* Traverse over all the splay trees of the basic blocks.  */
  for (i = 0; i < last_bb; i++)
    {
      if (see_bb_splay_ar[i])
	{
	  if (dump_file)
	    fprintf (dump_file, "Handling references for bb %d\n", i);
	  /* Traverse over all the references in the basic block in forward
	     order.  */
	  splay_tree_foreach (see_bb_splay_ar[i],
			      see_handle_extensions_for_one_ref, NULL);
	}
    }
}