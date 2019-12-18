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
struct sd {int /*<<< orphan*/  work_struct; int /*<<< orphan*/  work_thread; int /*<<< orphan*/  cap_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {int width; TYPE_1__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SQ905C_CAPTURE_HI ; 
 int /*<<< orphan*/  SQ905C_CAPTURE_INDEX ; 
 int /*<<< orphan*/  SQ905C_CAPTURE_MED ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sq905c_command (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *dev = (struct sd *) gspca_dev;
	int ret;

	dev->cap_mode = gspca_dev->cam.cam_mode;
	/* "Open the shutter" and set size, to start capture */
	switch (gspca_dev->width) {
	case 640:
		PDEBUG(D_STREAM, "Start streaming at high resolution");
		dev->cap_mode++;
		ret = sq905c_command(gspca_dev, SQ905C_CAPTURE_HI,
						SQ905C_CAPTURE_INDEX);
		break;
	default: /* 320 */
	PDEBUG(D_STREAM, "Start streaming at medium resolution");
		ret = sq905c_command(gspca_dev, SQ905C_CAPTURE_MED,
						SQ905C_CAPTURE_INDEX);
	}

	if (ret < 0) {
		PDEBUG(D_ERR, "Start streaming command failed");
		return ret;
	}
	/* Start the workqueue function to do the streaming */
	dev->work_thread = create_singlethread_workqueue(MODULE_NAME);
	queue_work(dev->work_thread, &dev->work_struct);

	return 0;
}