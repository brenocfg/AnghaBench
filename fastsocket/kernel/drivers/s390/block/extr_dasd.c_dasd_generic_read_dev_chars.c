#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int /*<<< orphan*/  memdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int PTR_ERR (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_generic_build_rdc (struct dasd_device*,void*,int,int) ; 
 int /*<<< orphan*/  dasd_sfree_request (struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 
 int dasd_sleep_on (struct dasd_ccw_req*) ; 

int dasd_generic_read_dev_chars(struct dasd_device *device, int magic,
				void *rdc_buffer, int rdc_buffer_size)
{
	int ret;
	struct dasd_ccw_req *cqr;

	cqr = dasd_generic_build_rdc(device, rdc_buffer, rdc_buffer_size,
				     magic);
	if (IS_ERR(cqr))
		return PTR_ERR(cqr);

	ret = dasd_sleep_on(cqr);
	dasd_sfree_request(cqr, cqr->memdev);
	return ret;
}