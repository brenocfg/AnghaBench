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
struct pp_cam_entry {int /*<<< orphan*/  port; scalar_t__ streaming; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  cpia_parport_disable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpia_pp_streamStop(void *privdata)
{
	struct pp_cam_entry *cam = privdata;

	DBG("\n");
	cam->streaming=0;
	cpia_parport_disable_irq(cam->port);
	//EndTransferMode(cam);

	return 0;
}