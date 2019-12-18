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
struct TYPE_7__ {int /*<<< orphan*/  pam; } ;
struct TYPE_8__ {TYPE_2__ pmcw; } ;
struct subchannel {TYPE_3__ schib; int /*<<< orphan*/  lpm; scalar_t__ vpm; } ;
struct ccw_request {int lpm; int singlepath; int /*<<< orphan*/  callback; int /*<<< orphan*/  filter; int /*<<< orphan*/  maxretries; int /*<<< orphan*/  timeout; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_5__* private; TYPE_1__ dev; } ;
struct ccw_dev_id {int dummy; } ;
struct TYPE_9__ {scalar_t__ pgroup; } ;
struct TYPE_10__ {TYPE_4__ flags; struct ccw_dev_id dev_id; struct ccw_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int,struct ccw_dev_id*,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  PGID_RETRIES ; 
 int /*<<< orphan*/  PGID_TIMEOUT ; 
 int /*<<< orphan*/  memset (struct ccw_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nop_callback ; 
 int /*<<< orphan*/  nop_do (struct ccw_device*) ; 
 int /*<<< orphan*/  nop_filter ; 
 int /*<<< orphan*/  snid_callback ; 
 int /*<<< orphan*/  snid_do (struct ccw_device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verify_start(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_request *req = &cdev->private->req;
	struct ccw_dev_id *devid = &cdev->private->dev_id;

	sch->vpm = 0;
	sch->lpm = sch->schib.pmcw.pam;
	/* Initialize request data. */
	memset(req, 0, sizeof(*req));
	req->timeout	= PGID_TIMEOUT;
	req->maxretries	= PGID_RETRIES;
	req->lpm	= 0x80;
	req->singlepath	= 1;
	if (cdev->private->flags.pgroup) {
		CIO_TRACE_EVENT(4, "snid");
		CIO_HEX_EVENT(4, devid, sizeof(*devid));
		req->callback	= snid_callback;
		snid_do(cdev);
	} else {
		CIO_TRACE_EVENT(4, "nop");
		CIO_HEX_EVENT(4, devid, sizeof(*devid));
		req->filter	= nop_filter;
		req->callback	= nop_callback;
		nop_do(cdev);
	}
}