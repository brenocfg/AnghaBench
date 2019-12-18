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
struct uvd {int last_error; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  err (char*,char const*) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ultracam_alternateSetting(struct uvd *uvd, int setting)
{
	static const char proc[] = "ultracam_alternateSetting";
	int i;
	i = usb_set_interface(uvd->dev, uvd->iface, setting);
	if (i < 0) {
		err("%s: usb_set_interface error", proc);
		uvd->last_error = i;
		return -EBUSY;
	}
	return 0;
}