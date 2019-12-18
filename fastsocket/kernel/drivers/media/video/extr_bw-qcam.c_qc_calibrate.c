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
struct qcam_device {int whitebal; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  qc_command (struct qcam_device*,int) ; 
 int qc_readparam (struct qcam_device*) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static int qc_calibrate(struct qcam_device *q)
{
	/*
	 *	Bugfix by Hanno Mueller hmueller@kabel.de, Mai 21 96
	 *	The white balance is an individiual value for each
	 *	quickcam.
	 */

	int value;
	int count = 0;

	qc_command(q, 27);	/* AutoAdjustOffset */
	qc_command(q, 0);	/* Dummy Parameter, ignored by the camera */

	/* GetOffset (33) will read 255 until autocalibration */
	/* is finished. After that, a value of 1-254 will be */
	/* returned. */

	do {
		qc_command(q, 33);
		value = qc_readparam(q);
		mdelay(1);
		schedule();
		count++;
	} while (value == 0xff && count<2048);

	q->whitebal = value;
	return value;
}