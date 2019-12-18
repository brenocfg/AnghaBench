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
struct dasd_device {TYPE_1__* cdev; } ;
struct dasd_ccw_req {int expires; int retries; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; struct dasd_device* memdev; struct dasd_device* startdev; scalar_t__ data; struct ccw1* cpaddr; } ;
struct ccw1 {int count; scalar_t__ flags; void* cda; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ addr_t ;
typedef  void* __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_RDC ; 
 scalar_t__ CCW_FLAG_IDA ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_smalloc_request (int,int,int,struct dasd_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  get_clock () ; 
 unsigned long* idal_create_words (unsigned long*,void*,int) ; 
 scalar_t__ idal_is_needed (void*,int) ; 

__attribute__((used)) static struct dasd_ccw_req *dasd_generic_build_rdc(struct dasd_device *device,
						   void *rdc_buffer,
						   int rdc_buffer_size,
						   int magic)
{
	struct dasd_ccw_req *cqr;
	struct ccw1 *ccw;
	unsigned long *idaw;

	cqr = dasd_smalloc_request(magic, 1 /* RDC */, rdc_buffer_size, device);

	if (IS_ERR(cqr)) {
		/* internal error 13 - Allocating the RDC request failed*/
		dev_err(&device->cdev->dev,
			 "An error occurred in the DASD device driver, "
			 "reason=%s\n", "13");
		return cqr;
	}

	ccw = cqr->cpaddr;
	ccw->cmd_code = CCW_CMD_RDC;
	if (idal_is_needed(rdc_buffer, rdc_buffer_size)) {
		idaw = (unsigned long *) (cqr->data);
		ccw->cda = (__u32)(addr_t) idaw;
		ccw->flags = CCW_FLAG_IDA;
		idaw = idal_create_words(idaw, rdc_buffer, rdc_buffer_size);
	} else {
		ccw->cda = (__u32)(addr_t) rdc_buffer;
		ccw->flags = 0;
	}

	ccw->count = rdc_buffer_size;
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->expires = 10*HZ;
	cqr->retries = 256;
	cqr->buildclk = get_clock();
	cqr->status = DASD_CQR_FILLED;
	return cqr;
}