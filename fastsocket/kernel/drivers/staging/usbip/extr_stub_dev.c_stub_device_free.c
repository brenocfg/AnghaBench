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
struct stub_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (struct stub_device*) ; 
 int /*<<< orphan*/  usbip_udbg (char*) ; 

__attribute__((used)) static int stub_device_free(struct stub_device *sdev)
{
	if (!sdev)
		return -EINVAL;

	kfree(sdev);
	usbip_udbg("kfree udev ok\n");

	return 0;
}