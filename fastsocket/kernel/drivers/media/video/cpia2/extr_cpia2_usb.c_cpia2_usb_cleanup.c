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

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  cpia2_driver ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  usb_deregister (int /*<<< orphan*/ *) ; 

void cpia2_usb_cleanup(void)
{
	schedule_timeout(2 * HZ);
	usb_deregister(&cpia2_driver);
}