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
struct usb_cpia {int /*<<< orphan*/  present; scalar_t__ open; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cpia_usb_free_resources (struct usb_cpia*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpia_usb_close(void *privdata)
{
	struct usb_cpia *ucpia = (struct usb_cpia *) privdata;

	if(!ucpia)
		return -ENODEV;

	ucpia->open = 0;

	/* ucpia->present = 0 protects against trying to reset the
	 * alt setting if camera is physically disconnected while open */
	cpia_usb_free_resources(ucpia, ucpia->present);

	return 0;
}