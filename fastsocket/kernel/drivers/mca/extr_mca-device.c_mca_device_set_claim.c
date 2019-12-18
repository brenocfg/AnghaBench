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
struct mca_device {int driver_loaded; } ;

/* Variables and functions */

void mca_device_set_claim(struct mca_device *mca_dev, int val)
{
	mca_dev->driver_loaded = val;
}