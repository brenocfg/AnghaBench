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
struct parisc_device {scalar_t__ driver; } ;

/* Variables and functions */

int register_parisc_device(struct parisc_device *dev)
{
	if (!dev)
		return 0;

	if (dev->driver)
		return 1;

	return 0;
}