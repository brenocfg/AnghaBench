#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_7__ {int pam; } ;
struct TYPE_8__ {TYPE_3__ pmcw; } ;
struct subchannel {int opm; TYPE_4__ schib; } ;
struct senseid {int dummy; } ;
struct ccw_request {int lpm; int /*<<< orphan*/  callback; int /*<<< orphan*/  check; int /*<<< orphan*/  maxretries; int /*<<< orphan*/  timeout; struct ccw1* cp; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_2__* private; TYPE_1__ dev; } ;
struct ccw1 {int count; int /*<<< orphan*/  flags; scalar_t__ cda; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  senseid; int /*<<< orphan*/  dev_id; struct ccw1* iccws; struct ccw_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_SENSE_ID ; 
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  CIO_HEX_EVENT (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  SENSE_ID_RETRIES ; 
 int /*<<< orphan*/  SENSE_ID_TIMEOUT ; 
 int /*<<< orphan*/  ccw_request_start (struct ccw_device*) ; 
 int /*<<< orphan*/  memset (struct ccw_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snsid_callback ; 
 int /*<<< orphan*/  snsid_check ; 
 int /*<<< orphan*/  snsid_init (struct ccw_device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

void ccw_device_sense_id_start(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_request *req = &cdev->private->req;
	struct ccw1 *cp = cdev->private->iccws;

	CIO_TRACE_EVENT(4, "snsid");
	CIO_HEX_EVENT(4, &cdev->private->dev_id, sizeof(cdev->private->dev_id));
	/* Data setup. */
	snsid_init(cdev);
	/* Channel program setup. */
	cp->cmd_code	= CCW_CMD_SENSE_ID;
	cp->cda		= (u32) (addr_t) &cdev->private->senseid;
	cp->count	= sizeof(struct senseid);
	cp->flags	= CCW_FLAG_SLI;
	/* Request setup. */
	memset(req, 0, sizeof(*req));
	req->cp		= cp;
	req->timeout	= SENSE_ID_TIMEOUT;
	req->maxretries	= SENSE_ID_RETRIES;
	req->lpm	= sch->schib.pmcw.pam & sch->opm;
	req->check	= snsid_check;
	req->callback	= snsid_callback;
	ccw_request_start(cdev);
}