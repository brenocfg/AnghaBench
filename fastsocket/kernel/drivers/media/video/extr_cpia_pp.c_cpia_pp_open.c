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
struct pp_cam_entry {scalar_t__ open_count; int /*<<< orphan*/  port; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IEEE1284_MODE_COMPAT ; 
 int PARPORT_CONTROL_INIT ; 
 int PARPORT_CONTROL_SELECT ; 
 scalar_t__ parport_claim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_data_forward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_negotiate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_write_control (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cpia_pp_open(void *privdata)
{
	struct pp_cam_entry *cam = (struct pp_cam_entry *)privdata;

	if (cam == NULL)
		return -EINVAL;

	if(cam->open_count == 0) {
		if (parport_claim(cam->pdev)) {
			DBG("failed to claim the port\n");
			return -EBUSY;
		}
		parport_negotiate(cam->port, IEEE1284_MODE_COMPAT);
		parport_data_forward(cam->port);
		parport_write_control(cam->port, PARPORT_CONTROL_SELECT);
		udelay(50);
		parport_write_control(cam->port,
				      PARPORT_CONTROL_SELECT
				      | PARPORT_CONTROL_INIT);
	}

	++cam->open_count;

	return 0;
}