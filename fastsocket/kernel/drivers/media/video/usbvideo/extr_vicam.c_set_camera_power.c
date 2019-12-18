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
struct vicam_camera {int dummy; } ;

/* Variables and functions */
 int send_control_msg (struct vicam_camera*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_camera_power(struct vicam_camera *cam, int state)
{
	int status;

	if ((status = send_control_msg(cam, 0x50, state, 0, NULL, 0)) < 0)
		return status;

	if (state) {
		send_control_msg(cam, 0x55, 1, 0, NULL, 0);
	}

	return 0;
}