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
struct pxafb_info {scalar_t__ state; unsigned long hsync_time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ C_ENABLE ; 
 struct pxafb_info* dev_get_drvdata (struct device*) ; 

unsigned long pxafb_get_hsync_time(struct device *dev)
{
	struct pxafb_info *fbi = dev_get_drvdata(dev);

	/* If display is blanked/suspended, hsync isn't active */
	if (!fbi || (fbi->state != C_ENABLE))
		return 0;

	return fbi->hsync_time;
}