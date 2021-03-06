#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  msg; int /*<<< orphan*/  ioa_state; } ;
struct pmcraid_instance {TYPE_1__ scn; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmcraid_notify_aen (struct pmcraid_instance*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pmcraid_notify_ioastate(struct pmcraid_instance *pinstance, u32 evt)
{
	pinstance->scn.ioa_state = evt;
	pmcraid_notify_aen(pinstance,
			  &pinstance->scn.msg,
			  sizeof(u32));
}