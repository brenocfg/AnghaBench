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
struct pp_cam_entry {scalar_t__ open_count; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  parport_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpia_pp_close(void *privdata)
{
	struct pp_cam_entry *cam = privdata;
	if (--cam->open_count == 0) {
		parport_release(cam->pdev);
	}
	return 0;
}