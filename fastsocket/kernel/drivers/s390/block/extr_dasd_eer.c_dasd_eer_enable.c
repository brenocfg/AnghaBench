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
struct dasd_device {int /*<<< orphan*/  cdev; struct dasd_ccw_req* eer_cqr; TYPE_1__* discipline; } ;
struct dasd_ccw_req {int retries; int expires; int /*<<< orphan*/  callback; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; scalar_t__ data; struct ccw1* cpaddr; int /*<<< orphan*/  flags; struct dasd_device* startdev; } ;
struct ccw1 {scalar_t__ cda; int /*<<< orphan*/  flags; int /*<<< orphan*/  count; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ addr_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_ALLOW_SLOCK ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_FLAGS_USE_ERP ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_SNSS ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int ENOMEM ; 
 int EPERM ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  SNSS_DATA_SIZE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_eer_snss_cb ; 
 int /*<<< orphan*/  dasd_kfree_request (struct dasd_ccw_req*,struct dasd_device*) ; 
 struct dasd_ccw_req* dasd_kmalloc_request (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dasd_device*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_clock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int dasd_eer_enable(struct dasd_device *device)
{
	struct dasd_ccw_req *cqr;
	unsigned long flags;
	struct ccw1 *ccw;

	if (device->eer_cqr)
		return 0;

	if (!device->discipline || strcmp(device->discipline->name, "ECKD"))
		return -EPERM;	/* FIXME: -EMEDIUMTYPE ? */

	cqr = dasd_kmalloc_request(DASD_ECKD_MAGIC, 1 /* SNSS */,
				   SNSS_DATA_SIZE, device);
	if (IS_ERR(cqr))
		return -ENOMEM;

	cqr->startdev = device;
	cqr->retries = 255;
	cqr->expires = 10 * HZ;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	set_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags);

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_SNSS;
	ccw->count = SNSS_DATA_SIZE;
	ccw->flags = 0;
	ccw->cda = (__u32)(addr_t) cqr->data;

	cqr->buildclk = get_clock();
	cqr->status = DASD_CQR_FILLED;
	cqr->callback = dasd_eer_snss_cb;

	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	if (!device->eer_cqr) {
		device->eer_cqr = cqr;
		cqr = NULL;
	}
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	if (cqr)
		dasd_kfree_request(cqr, device);
	return 0;
}