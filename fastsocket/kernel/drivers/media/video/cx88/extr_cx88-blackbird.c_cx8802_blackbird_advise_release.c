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
struct cx88_core {int boardnr; } ;
struct cx8802_driver {struct cx88_core* core; } ;

/* Variables and functions */
#define  CX88_BOARD_HAUPPAUGE_HVR1300 128 
 int ENODEV ; 

__attribute__((used)) static int cx8802_blackbird_advise_release(struct cx8802_driver *drv)
{
	struct cx88_core *core = drv->core;
	int err = 0;

	switch (core->boardnr) {
	case CX88_BOARD_HAUPPAUGE_HVR1300:
		/* Exit leaving the cx23416 on the bus */
		break;
	default:
		err = -ENODEV;
	}
	return err;
}