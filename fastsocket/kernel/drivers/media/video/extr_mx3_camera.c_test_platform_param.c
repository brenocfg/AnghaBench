#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ v4l2_dev; } ;
struct mx3_camera_dev {int platform_flags; TYPE_2__ soc_host; } ;

/* Variables and functions */
 int EINVAL ; 
 int MX3_CAMERA_DATAWIDTH_10 ; 
 int MX3_CAMERA_DATAWIDTH_15 ; 
 int MX3_CAMERA_DATAWIDTH_4 ; 
 int MX3_CAMERA_DATAWIDTH_8 ; 
 unsigned long SOCAM_DATAWIDTH_10 ; 
 unsigned long SOCAM_DATAWIDTH_15 ; 
 unsigned long SOCAM_DATAWIDTH_4 ; 
 unsigned long SOCAM_DATAWIDTH_8 ; 
 unsigned long SOCAM_DATA_ACTIVE_HIGH ; 
 unsigned long SOCAM_DATA_ACTIVE_LOW ; 
 unsigned long SOCAM_HSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_HSYNC_ACTIVE_LOW ; 
 unsigned long SOCAM_MASTER ; 
 unsigned long SOCAM_PCLK_SAMPLE_FALLING ; 
 unsigned long SOCAM_PCLK_SAMPLE_RISING ; 
 unsigned long SOCAM_VSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned char) ; 

__attribute__((used)) static int test_platform_param(struct mx3_camera_dev *mx3_cam,
			       unsigned char buswidth, unsigned long *flags)
{
	/*
	 * Platform specified synchronization and pixel clock polarities are
	 * only a recommendation and are only used during probing. MX3x
	 * camera interface only works in master mode, i.e., uses HSYNC and
	 * VSYNC signals from the sensor
	 */
	*flags = SOCAM_MASTER |
		SOCAM_HSYNC_ACTIVE_HIGH |
		SOCAM_HSYNC_ACTIVE_LOW |
		SOCAM_VSYNC_ACTIVE_HIGH |
		SOCAM_VSYNC_ACTIVE_LOW |
		SOCAM_PCLK_SAMPLE_RISING |
		SOCAM_PCLK_SAMPLE_FALLING |
		SOCAM_DATA_ACTIVE_HIGH |
		SOCAM_DATA_ACTIVE_LOW;

	/* If requested data width is supported by the platform, use it or any
	 * possible lower value - i.MX31 is smart enough to schift bits */
	switch (buswidth) {
	case 15:
		if (!(mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_15))
			return -EINVAL;
		*flags |= SOCAM_DATAWIDTH_15 | SOCAM_DATAWIDTH_10 |
			SOCAM_DATAWIDTH_8 | SOCAM_DATAWIDTH_4;
		break;
	case 10:
		if (!(mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_10))
			return -EINVAL;
		*flags |= SOCAM_DATAWIDTH_10 | SOCAM_DATAWIDTH_8 |
			SOCAM_DATAWIDTH_4;
		break;
	case 8:
		if (!(mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_8))
			return -EINVAL;
		*flags |= SOCAM_DATAWIDTH_8 | SOCAM_DATAWIDTH_4;
		break;
	case 4:
		if (!(mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_4))
			return -EINVAL;
		*flags |= SOCAM_DATAWIDTH_4;
		break;
	default:
		dev_warn(mx3_cam->soc_host.v4l2_dev.dev,
			 "Unsupported bus width %d\n", buswidth);
		return -EINVAL;
	}

	return 0;
}