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
struct ehl_map_entry {struct eh_region* region; int /*<<< orphan*/  label; } ;
struct eh_region {scalar_t__ type; int /*<<< orphan*/  label; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int /*<<< orphan*/  exception_handler_label_map; scalar_t__ built_landing_pads; } ;

/* Variables and functions */
 scalar_t__ ERT_MUST_NOT_THROW ; 
 int /*<<< orphan*/  NO_INSERT ; 
 int /*<<< orphan*/  NULL_RTX ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  htab_clear_slot (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ htab_find_slot (int /*<<< orphan*/ ,struct ehl_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_eh_handler (struct eh_region*) ; 

void
maybe_remove_eh_handler (rtx label)
{
  struct ehl_map_entry **slot, tmp;
  struct eh_region *region;

  /* ??? After generating landing pads, it's not so simple to determine
     if the region data is completely unused.  One must examine the
     landing pad and the post landing pad, and whether an inner try block
     is referencing the catch handlers directly.  */
  if (cfun->eh->built_landing_pads)
    return;

  tmp.label = label;
  slot = (struct ehl_map_entry **)
    htab_find_slot (cfun->eh->exception_handler_label_map, &tmp, NO_INSERT);
  if (! slot)
    return;
  region = (*slot)->region;
  if (! region)
    return;

  /* Flow will want to remove MUST_NOT_THROW regions as unreachable
     because there is no path to the fallback call to terminate.
     But the region continues to affect call-site data until there
     are no more contained calls, which we don't see here.  */
  if (region->type == ERT_MUST_NOT_THROW)
    {
      htab_clear_slot (cfun->eh->exception_handler_label_map, (void **) slot);
      region->label = NULL_RTX;
    }
  else
    remove_eh_handler (region);
}