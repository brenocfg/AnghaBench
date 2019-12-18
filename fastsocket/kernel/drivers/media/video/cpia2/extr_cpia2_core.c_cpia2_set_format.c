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
struct camera_data {int flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpia2_dbg_dump_registers (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_reset_camera (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_set_low_power (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_usb_stream_pause (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_usb_stream_resume (struct camera_data*) ; 

void cpia2_set_format(struct camera_data *cam)
{
	cam->flush = true;

	cpia2_usb_stream_pause(cam);

	/* reset camera to new size */
	cpia2_set_low_power(cam);
	cpia2_reset_camera(cam);
	cam->flush = false;

	cpia2_dbg_dump_registers(cam);

	cpia2_usb_stream_resume(cam);
}