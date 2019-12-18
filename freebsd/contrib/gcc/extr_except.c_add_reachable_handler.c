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
struct reachable_info {int saw_any_handlers; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* callback ) (struct eh_region*,int /*<<< orphan*/ ) ;} ;
struct eh_region {int dummy; } ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {scalar_t__ built_landing_pads; } ;

/* Variables and functions */
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  stub1 (struct eh_region*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct eh_region*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_reachable_handler (struct reachable_info *info,
		       struct eh_region *lp_region, struct eh_region *region)
{
  if (! info)
    return;

  info->saw_any_handlers = true;

  if (cfun->eh->built_landing_pads)
    info->callback (lp_region, info->callback_data);
  else
    info->callback (region, info->callback_data);
}