#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pp_cam_entry {void (* cb_func ) (void*) ;int /*<<< orphan*/  cb_task; void* cb_data; TYPE_1__* port; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PARPORT_IRQ_NONE ; 
 int /*<<< orphan*/  cpia_pp_run_callback ; 

__attribute__((used)) static int cpia_pp_registerCallback(void *privdata, void (*cb)(void *cbdata), void *cbdata)
{
	struct pp_cam_entry *cam = privdata;
	int retval = 0;

	if(cam->port->irq != PARPORT_IRQ_NONE) {
		cam->cb_func = cb;
		cam->cb_data = cbdata;
		INIT_WORK(&cam->cb_task, cpia_pp_run_callback);
	} else {
		retval = -1;
	}
	return retval;
}