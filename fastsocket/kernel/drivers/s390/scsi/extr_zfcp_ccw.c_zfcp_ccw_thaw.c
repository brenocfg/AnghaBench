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
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_ccw_activate (struct ccw_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int zfcp_ccw_thaw(struct ccw_device *cdev)
{
	/* trace records for thaw and final shutdown during suspend
	   can only be found in system dump until the end of suspend
	   but not after resume because it's based on the memory image
	   right after the very first suspend (freeze) callback */
	zfcp_ccw_activate(cdev, 0, "ccthaw1");
	return 0;
}