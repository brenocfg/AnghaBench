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
struct eh_region {int region_number; scalar_t__ label; scalar_t__ landing_pad; } ;
typedef  scalar_t__ rtx ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int last_region_number; scalar_t__ built_landing_pads; int /*<<< orphan*/  region_array; int /*<<< orphan*/ * region_tree; scalar_t__ exception_handler_label_map; } ;

/* Variables and functions */
 scalar_t__ USING_SJLJ_EXCEPTIONS ; 
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_ehl_entry (scalar_t__,struct eh_region*) ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  ehl_eq ; 
 int /*<<< orphan*/  ehl_hash ; 
 scalar_t__ htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_empty (scalar_t__) ; 
 scalar_t__ return_label ; 

void
find_exception_handler_labels (void)
{
  int i;

  if (cfun->eh->exception_handler_label_map)
    htab_empty (cfun->eh->exception_handler_label_map);
  else
    {
      /* ??? The expansion factor here (3/2) must be greater than the htab
	 occupancy factor (4/3) to avoid unnecessary resizing.  */
      cfun->eh->exception_handler_label_map
        = htab_create_ggc (cfun->eh->last_region_number * 3 / 2,
			   ehl_hash, ehl_eq, NULL);
    }

  if (cfun->eh->region_tree == NULL)
    return;

  for (i = cfun->eh->last_region_number; i > 0; --i)
    {
      struct eh_region *region;
      rtx lab;

      region = VEC_index (eh_region, cfun->eh->region_array, i);
      if (! region || region->region_number != i)
	continue;
      if (cfun->eh->built_landing_pads)
	lab = region->landing_pad;
      else
	lab = region->label;

      if (lab)
	add_ehl_entry (lab, region);
    }

  /* For sjlj exceptions, need the return label to remain live until
     after landing pad generation.  */
  if (USING_SJLJ_EXCEPTIONS && ! cfun->eh->built_landing_pads)
    add_ehl_entry (return_label, NULL);
}