#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct eh_region {int dummy; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {size_t index; } ;

/* Variables and functions */
 scalar_t__ get_eh_region_tree_label (struct eh_region*) ; 
 scalar_t__* label_for_bb ; 
 TYPE_1__* label_to_block (scalar_t__) ; 
 int /*<<< orphan*/  set_eh_region_tree_label (struct eh_region*,scalar_t__) ; 

__attribute__((used)) static void
update_eh_label (struct eh_region *region)
{
  tree old_label = get_eh_region_tree_label (region);
  if (old_label)
    {
      tree new_label;
      basic_block bb = label_to_block (old_label);

      /* ??? After optimizing, there may be EH regions with labels
	 that have already been removed from the function body, so
	 there is no basic block for them.  */
      if (! bb)
	return;

      new_label = label_for_bb[bb->index];
      set_eh_region_tree_label (region, new_label);
    }
}