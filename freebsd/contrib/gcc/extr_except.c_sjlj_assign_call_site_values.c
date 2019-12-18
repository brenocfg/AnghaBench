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
struct sjlj_lp_info {int action_index; int call_site_index; int /*<<< orphan*/  dispatch_index; scalar_t__ directly_reachable; } ;
struct eh_region {int /*<<< orphan*/  landing_pad; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  htab_t ;
struct TYPE_4__ {int uses_eh_lsda; TYPE_1__* eh; } ;
struct TYPE_3__ {int last_region_number; int /*<<< orphan*/  region_array; int /*<<< orphan*/  action_record_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARRAY_UCHAR_INIT (int /*<<< orphan*/ ,int,char*) ; 
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  action_record_eq ; 
 int /*<<< orphan*/  action_record_hash ; 
 int add_call_site (int /*<<< orphan*/ ,int) ; 
 int call_site_base ; 
 TYPE_2__* cfun ; 
 int collect_one_action_chain (int /*<<< orphan*/ ,struct eh_region*) ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sjlj_assign_call_site_values (rtx dispatch_label, struct sjlj_lp_info *lp_info)
{
  htab_t ar_hash;
  int i, index;

  /* First task: build the action table.  */

  VARRAY_UCHAR_INIT (cfun->eh->action_record_data, 64, "action_record_data");
  ar_hash = htab_create (31, action_record_hash, action_record_eq, free);

  for (i = cfun->eh->last_region_number; i > 0; --i)
    if (lp_info[i].directly_reachable)
      {
	struct eh_region *r = VEC_index (eh_region, cfun->eh->region_array, i);

	r->landing_pad = dispatch_label;
	lp_info[i].action_index = collect_one_action_chain (ar_hash, r);
	if (lp_info[i].action_index != -1)
	  cfun->uses_eh_lsda = 1;
      }

  htab_delete (ar_hash);

  /* Next: assign dispatch values.  In dwarf2 terms, this would be the
     landing pad label for the region.  For sjlj though, there is one
     common landing pad from which we dispatch to the post-landing pads.

     A region receives a dispatch index if it is directly reachable
     and requires in-function processing.  Regions that share post-landing
     pads may share dispatch indices.  */
  /* ??? Post-landing pad sharing doesn't actually happen at the moment
     (see build_post_landing_pads) so we don't bother checking for it.  */

  index = 0;
  for (i = cfun->eh->last_region_number; i > 0; --i)
    if (lp_info[i].directly_reachable)
      lp_info[i].dispatch_index = index++;

  /* Finally: assign call-site values.  If dwarf2 terms, this would be
     the region number assigned by convert_to_eh_region_ranges, but
     handles no-action and must-not-throw differently.  */

  call_site_base = 1;
  for (i = cfun->eh->last_region_number; i > 0; --i)
    if (lp_info[i].directly_reachable)
      {
	int action = lp_info[i].action_index;

	/* Map must-not-throw to otherwise unused call-site index 0.  */
	if (action == -2)
	  index = 0;
	/* Map no-action to otherwise unused call-site index -1.  */
	else if (action == -1)
	  index = -1;
	/* Otherwise, look it up in the table.  */
	else
	  index = add_call_site (GEN_INT (lp_info[i].dispatch_index), action);

	lp_info[i].call_site_index = index;
      }
}