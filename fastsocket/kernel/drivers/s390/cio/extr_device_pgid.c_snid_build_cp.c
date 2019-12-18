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
typedef  scalar_t__ u32 ;
struct pgid {int dummy; } ;
struct ccw_request {struct ccw1* cp; int /*<<< orphan*/  lpm; } ;
struct ccw_device {TYPE_1__* private; } ;
struct ccw1 {int count; int /*<<< orphan*/  flags; scalar_t__ cda; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pgid; struct ccw1* iccws; struct ccw_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_SENSE_PGID ; 
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snid_build_cp(struct ccw_device *cdev)
{
	struct ccw_request *req = &cdev->private->req;
	struct ccw1 *cp = cdev->private->iccws;
	int i = 8 - ffs(req->lpm);

	/* Channel program setup. */
	cp->cmd_code	= CCW_CMD_SENSE_PGID;
	cp->cda		= (u32) (addr_t) &cdev->private->pgid[i];
	cp->count	= sizeof(struct pgid);
	cp->flags	= CCW_FLAG_SLI;
	req->cp		= cp;
}