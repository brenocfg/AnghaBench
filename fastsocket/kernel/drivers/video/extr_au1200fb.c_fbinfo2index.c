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
struct fb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb_info; } ;

/* Variables and functions */
 int CONFIG_FB_AU1200_DEVS ; 
 TYPE_1__* _au1200fb_devices ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int fbinfo2index (struct fb_info *fb_info)
{
	int i;

	for (i = 0; i < CONFIG_FB_AU1200_DEVS; ++i) {
		if (fb_info == (struct fb_info *)(&_au1200fb_devices[i].fb_info))
			return i;
	}
	printk("au1200fb: ERROR: fbinfo2index failed!\n");
	return -1;
}