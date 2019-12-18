#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * chpid; } ;
struct TYPE_6__ {TYPE_2__ pmcw; } ;
struct subchannel {TYPE_3__ schib; } ;
struct chp_id {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_1__ dev; } ;

/* Variables and functions */
 void* chp_get_chp_desc (struct chp_id) ; 
 int /*<<< orphan*/  chp_id_init (struct chp_id*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

void *ccw_device_get_chp_desc(struct ccw_device *cdev, int chp_no)
{
	struct subchannel *sch;
	struct chp_id chpid;

	sch = to_subchannel(cdev->dev.parent);
	chp_id_init(&chpid);
	chpid.id = sch->schib.pmcw.chpid[chp_no];
	return chp_get_chp_desc(chpid);
}