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
struct dasd_rssd_features {int suborder; int /*<<< orphan*/  order; } ;
struct dasd_psf_prssd_data {int suborder; int /*<<< orphan*/  order; } ;
struct dasd_eckd_private {struct dasd_rssd_features features; } ;
struct dasd_device {TYPE_1__* cdev; scalar_t__ private; } ;
struct dasd_ccw_req {int retries; int expires; struct dasd_device* memdev; scalar_t__ data; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; struct ccw1* cpaddr; int /*<<< orphan*/ * block; struct dasd_device* startdev; } ;
struct ccw1 {int count; void* cda; int /*<<< orphan*/  cmd_code; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ addr_t ;
typedef  void* __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_CC ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_PSF ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_RSSD ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  PSF_ORDER_PRSSD ; 
 int PTR_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  dasd_sfree_request (struct dasd_ccw_req*,struct dasd_device*) ; 
 int dasd_sleep_on (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_smalloc_request (int /*<<< orphan*/ ,int,int,struct dasd_device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  get_clock () ; 
 int /*<<< orphan*/  memcpy (struct dasd_rssd_features*,struct dasd_rssd_features*,int) ; 
 int /*<<< orphan*/  memset (struct dasd_rssd_features*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dasd_eckd_read_features(struct dasd_device *device)
{
	struct dasd_psf_prssd_data *prssdp;
	struct dasd_rssd_features *features;
	struct dasd_ccw_req *cqr;
	struct ccw1 *ccw;
	int rc;
	struct dasd_eckd_private *private;

	private = (struct dasd_eckd_private *) device->private;
	memset(&private->features, 0, sizeof(struct dasd_rssd_features));
	cqr = dasd_smalloc_request(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* RSSD */,
				   (sizeof(struct dasd_psf_prssd_data) +
				    sizeof(struct dasd_rssd_features)),
				   device);
	if (IS_ERR(cqr)) {
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s", "Could not "
				"allocate initialization request");
		return PTR_ERR(cqr);
	}
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = NULL;
	cqr->retries = 256;
	cqr->expires = 10 * HZ;

	/* Prepare for Read Subsystem Data */
	prssdp = (struct dasd_psf_prssd_data *) cqr->data;
	memset(prssdp, 0, sizeof(struct dasd_psf_prssd_data));
	prssdp->order = PSF_ORDER_PRSSD;
	prssdp->suborder = 0x41;	/* Read Feature Codes */
	/* all other bytes of prssdp must be zero */

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(struct dasd_psf_prssd_data);
	ccw->flags |= CCW_FLAG_CC;
	ccw->cda = (__u32)(addr_t) prssdp;

	/* Read Subsystem Data - feature codes */
	features = (struct dasd_rssd_features *) (prssdp + 1);
	memset(features, 0, sizeof(struct dasd_rssd_features));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = sizeof(struct dasd_rssd_features);
	ccw->cda = (__u32)(addr_t) features;

	cqr->buildclk = get_clock();
	cqr->status = DASD_CQR_FILLED;
	rc = dasd_sleep_on(cqr);
	if (rc == 0) {
		prssdp = (struct dasd_psf_prssd_data *) cqr->data;
		features = (struct dasd_rssd_features *) (prssdp + 1);
		memcpy(&private->features, features,
		       sizeof(struct dasd_rssd_features));
	} else
		dev_warn(&device->cdev->dev, "Reading device feature codes"
			 " failed with rc=%d\n", rc);
	dasd_sfree_request(cqr, cqr->memdev);
	return rc;
}