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
struct pp_cam_entry {int streaming; int /*<<< orphan*/  port; scalar_t__ stream_irq; scalar_t__ image_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  cpia_parport_enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpia_pp_streamStart(void *privdata)
{
	struct pp_cam_entry *cam = privdata;
	DBG("\n");
	cam->streaming=1;
	cam->image_ready=0;
	//if (ReverseSetup(cam,1)) return -EIO;
	if(cam->stream_irq) cpia_parport_enable_irq(cam->port);
	return 0;
}