#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct eh_region {scalar_t__ tree_label; int /*<<< orphan*/  label; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int last_region_number; int /*<<< orphan*/  region_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_RTL_IF_SET (scalar_t__) ; 
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  remove_unreachable_regions (int /*<<< orphan*/ ) ; 

void
convert_from_eh_region_ranges (void)
{
  rtx insns = get_insns ();
  int i, n = cfun->eh->last_region_number;

  /* Most of the work is already done at the tree level.  All we need to
     do is collect the rtl labels that correspond to the tree labels that
     collect the rtl labels that correspond to the tree labels
     we allocated earlier.  */
  for (i = 1; i <= n; ++i)
    {
      struct eh_region *region;

      region = VEC_index (eh_region, cfun->eh->region_array, i);
      if (region && region->tree_label)
	region->label = DECL_RTL_IF_SET (region->tree_label);
    }

  remove_unreachable_regions (insns);
}