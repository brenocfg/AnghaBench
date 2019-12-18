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
struct iforce {int bus; } ;

/* Variables and functions */
#define  IFORCE_232 129 
#define  IFORCE_USB 128 
 int /*<<< orphan*/  iforce_usb_delete (struct iforce*) ; 

void iforce_delete_device(struct iforce *iforce)
{
	switch (iforce->bus) {
#ifdef CONFIG_JOYSTICK_IFORCE_USB
	case IFORCE_USB:
		iforce_usb_delete(iforce);
		break;
#endif
#ifdef CONFIG_JOYSTICK_IFORCE_232
	case IFORCE_232:
		//TODO: Wait for the last packets to be sent
		break;
#endif
	}
}