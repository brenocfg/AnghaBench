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
struct dasd_device {int /*<<< orphan*/  flags; } ;
struct dasd_ccw_req {int count; int retries; int expires; struct dasd_device* memdev; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; int /*<<< orphan*/  flags; struct dasd_device* startdev; int /*<<< orphan*/ * data; scalar_t__ cda; int /*<<< orphan*/  cmd_code; struct dasd_ccw_req* cpaddr; int /*<<< orphan*/  magic; } ;
struct ccw1 {int count; int retries; int expires; struct dasd_device* memdev; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; int /*<<< orphan*/  flags; struct dasd_device* startdev; int /*<<< orphan*/ * data; scalar_t__ cda; int /*<<< orphan*/  cmd_code; struct ccw1* cpaddr; int /*<<< orphan*/  magic; } ;
typedef  scalar_t__ addr_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  data; struct dasd_ccw_req ccw; struct dasd_ccw_req cqr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_FLAGS_FAILFAST ; 
 int /*<<< orphan*/  DASD_CQR_FLAGS_USE_ERP ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_SLCK ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int /*<<< orphan*/  DASD_FLAG_IS_RESERVED ; 
 int EACCES ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_reserve_mutex ; 
 TYPE_1__* dasd_reserve_req ; 
 int /*<<< orphan*/  dasd_sfree_request (struct dasd_ccw_req*,struct dasd_device*) ; 
 int dasd_sleep_on_immediatly (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_smalloc_request (int /*<<< orphan*/ ,int,int,struct dasd_device*) ; 
 int /*<<< orphan*/  get_clock () ; 
 int /*<<< orphan*/  memset (struct dasd_ccw_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dasd_eckd_steal_lock(struct dasd_device *device)
{
	struct dasd_ccw_req *cqr;
	int rc;
	struct ccw1 *ccw;
	int useglobal;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	useglobal = 0;
	cqr = dasd_smalloc_request(DASD_ECKD_MAGIC, 1, 32, device);
	if (IS_ERR(cqr)) {
		mutex_lock(&dasd_reserve_mutex);
		useglobal = 1;
		cqr = &dasd_reserve_req->cqr;
		memset(cqr, 0, sizeof(*cqr));
		memset(&dasd_reserve_req->ccw, 0,
		       sizeof(dasd_reserve_req->ccw));
		cqr->cpaddr = &dasd_reserve_req->ccw;
		cqr->data = &dasd_reserve_req->data;
		cqr->magic = DASD_ECKD_MAGIC;
	}
	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_SLCK;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->count = 32;
	ccw->cda = (__u32)(addr_t) cqr->data;
	cqr->startdev = device;
	cqr->memdev = device;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->retries = 2;	/* set retry counter to enable basic ERP */
	cqr->expires = 2 * HZ;
	cqr->buildclk = get_clock();
	cqr->status = DASD_CQR_FILLED;

	rc = dasd_sleep_on_immediatly(cqr);
	if (!rc)
		set_bit(DASD_FLAG_IS_RESERVED, &device->flags);

	if (useglobal)
		mutex_unlock(&dasd_reserve_mutex);
	else
		dasd_sfree_request(cqr, cqr->memdev);
	return rc;
}