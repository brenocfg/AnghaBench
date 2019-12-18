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
struct dasd_device {int /*<<< orphan*/  cdev; } ;
struct dasd_ccw_req {int /*<<< orphan*/  memdev; int /*<<< orphan*/  callback; } ;
struct ciw {scalar_t__ cmd; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CIW_TYPE_RCD ; 
 scalar_t__ DASD_ECKD_CCW_RCD ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int DASD_ECKD_RCD_DATA_SIZE ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 struct ciw* ccw_device_get_ciw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_eckd_fill_rcd_cqr (struct dasd_device*,struct dasd_ccw_req*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_sfree_request (struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 
 int dasd_sleep_on (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_smalloc_request (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dasd_device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int) ; 
 int /*<<< orphan*/  read_conf_cb ; 

__attribute__((used)) static int dasd_eckd_read_conf_lpm(struct dasd_device *device,
				   void **rcd_buffer,
				   int *rcd_buffer_size, __u8 lpm)
{
	struct ciw *ciw;
	char *rcd_buf = NULL;
	int ret;
	struct dasd_ccw_req *cqr;

	/*
	 * sanity check: scan for RCD command in extended SenseID data
	 * some devices do not support RCD
	 */
	ciw = ccw_device_get_ciw(device->cdev, CIW_TYPE_RCD);
	if (!ciw || ciw->cmd != DASD_ECKD_CCW_RCD) {
		ret = -EOPNOTSUPP;
		goto out_error;
	}
	rcd_buf = kzalloc(DASD_ECKD_RCD_DATA_SIZE, GFP_KERNEL | GFP_DMA);
	if (!rcd_buf) {
		ret = -ENOMEM;
		goto out_error;
	}
	cqr = dasd_smalloc_request(DASD_ECKD_MAGIC, 1 /* RCD */,
				   0, /* use rcd_buf as data ara */
				   device);
	if (IS_ERR(cqr)) {
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "Could not allocate RCD request");
		ret = -ENOMEM;
		goto out_error;
	}
	dasd_eckd_fill_rcd_cqr(device, cqr, rcd_buf, lpm);
	cqr->callback = read_conf_cb;
	ret = dasd_sleep_on(cqr);
	/*
	 * on success we update the user input parms
	 */
	dasd_sfree_request(cqr, cqr->memdev);
	if (ret)
		goto out_error;

	*rcd_buffer_size = DASD_ECKD_RCD_DATA_SIZE;
	*rcd_buffer = rcd_buf;
	return 0;
out_error:
	kfree(rcd_buf);
	*rcd_buffer = NULL;
	*rcd_buffer_size = 0;
	return ret;
}