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
struct ni_gpct_device {struct ni_gpct_device* counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ni_gpct_device*) ; 

void ni_gpct_device_destroy(struct ni_gpct_device *counter_dev)
{
	if (counter_dev->counters == NULL)
		return;
	kfree(counter_dev->counters);
	kfree(counter_dev);
}