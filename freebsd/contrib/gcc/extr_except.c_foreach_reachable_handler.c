#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct reachable_info {void (* callback ) (struct eh_region*,void*) ;void* callback_data; } ;
struct TYPE_8__ {struct eh_region* prev_try; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {TYPE_3__ cleanup; TYPE_2__ throw; } ;
struct eh_region {scalar_t__ type; struct eh_region* outer; TYPE_4__ u; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_10__ {TYPE_1__* eh; } ;
struct TYPE_6__ {int /*<<< orphan*/  region_array; } ;

/* Variables and functions */
 scalar_t__ ERT_CLEANUP ; 
 scalar_t__ ERT_THROW ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ RNL_CAUGHT ; 
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* cfun ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  memset (struct reachable_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ reachable_next_level (struct eh_region*,int /*<<< orphan*/ ,struct reachable_info*) ; 

void
foreach_reachable_handler (int region_number, bool is_resx,
			   void (*callback) (struct eh_region *, void *),
			   void *callback_data)
{
  struct reachable_info info;
  struct eh_region *region;
  tree type_thrown;

  memset (&info, 0, sizeof (info));
  info.callback = callback;
  info.callback_data = callback_data;

  region = VEC_index (eh_region, cfun->eh->region_array, region_number);

  type_thrown = NULL_TREE;
  if (is_resx)
    {
      /* A RESX leaves a region instead of entering it.  Thus the
	 region itself may have been deleted out from under us.  */
      if (region == NULL)
	return;
      region = region->outer;
    }
  else if (region->type == ERT_THROW)
    {
      type_thrown = region->u.throw.type;
      region = region->outer;
    }

  while (region)
    {
      if (reachable_next_level (region, type_thrown, &info) >= RNL_CAUGHT)
	break;
      /* If we have processed one cleanup, there is no point in
	 processing any more of them.  Each cleanup will have an edge
	 to the next outer cleanup region, so the flow graph will be
	 accurate.  */
      if (region->type == ERT_CLEANUP)
	region = region->u.cleanup.prev_try;
      else
	region = region->outer;
    }
}