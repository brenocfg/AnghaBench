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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_GetCameraStatus ; 
 int /*<<< orphan*/  command_pause (struct gspca_dev*) ; 
 int /*<<< orphan*/  do_command (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goto_low_power (struct gspca_dev*) ; 
 int /*<<< orphan*/  save_camera_state (struct gspca_dev*) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	command_pause(gspca_dev);

	/* save camera state for later open (developers guide ch 3.5.3) */
	save_camera_state(gspca_dev);

	/* GotoLoPower */
	goto_low_power(gspca_dev);

	/* Update the camera status */
	do_command(gspca_dev, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0);
}