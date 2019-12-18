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
struct qcam_device {int brightness; int ccd_height; int ccd_width; int top; int left; int contrast; int whitebal; } ;

/* Variables and functions */
 int /*<<< orphan*/  qc_reset (struct qcam_device*) ; 
 int /*<<< orphan*/  qcam_set (struct qcam_device*,int,int) ; 

__attribute__((used)) static void qc_setup(struct qcam_device *q)
{
	qc_reset(q);

	/* Set the brightness.  */
	qcam_set(q, 11, q->brightness);

	/* Set the height and width.  These refer to the actual
	   CCD area *before* applying the selected decimation.  */
	qcam_set(q, 17, q->ccd_height);
	qcam_set(q, 19, q->ccd_width / 2);

	/* Set top and left.  */
	qcam_set(q, 0xd, q->top);
	qcam_set(q, 0xf, q->left);

	/* Set contrast and white balance.  */
	qcam_set(q, 0x19, q->contrast);
	qcam_set(q, 0x1f, q->whitebal);

	/* Set the speed.  */
	qcam_set(q, 45, 2);
}