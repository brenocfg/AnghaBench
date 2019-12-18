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
typedef  int u32 ;
struct TYPE_6__ {int* feature; } ;
struct dasd_eckd_private {TYPE_2__ features; TYPE_1__* gneq; } ;
struct dasd_device {TYPE_4__* cdev; scalar_t__ private; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int fcx; } ;
struct TYPE_5__ {int* reserved2; } ;

/* Variables and functions */
 int FCX_MAX_DATA_FACTOR ; 
 int ccw_device_get_mdc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ css_general_characteristics ; 
 scalar_t__ dasd_nofcx ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static u32 get_fcx_max_data(struct dasd_device *device)
{
#if defined(CONFIG_64BIT)
	int tpm, mdc;
	int fcx_in_css, fcx_in_gneq, fcx_in_features;
	struct dasd_eckd_private *private;

	if (dasd_nofcx)
		return 0;
	/* is transport mode supported? */
	private = (struct dasd_eckd_private *) device->private;
	fcx_in_css = css_general_characteristics.fcx;
	fcx_in_gneq = private->gneq->reserved2[7] & 0x04;
	fcx_in_features = private->features.feature[40] & 0x80;
	tpm = fcx_in_css && fcx_in_gneq && fcx_in_features;

	if (!tpm)
		return 0;

	mdc = ccw_device_get_mdc(device->cdev, 0);
	if (mdc < 0) {
		dev_warn(&device->cdev->dev, "Detecting the maximum supported"
			 " data size for zHPF requests failed\n");
		return 0;
	} else
		return mdc * FCX_MAX_DATA_FACTOR;
#else
	return 0;
#endif
}