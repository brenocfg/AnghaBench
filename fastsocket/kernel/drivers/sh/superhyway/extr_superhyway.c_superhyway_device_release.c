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
struct superhyway_device {struct superhyway_device* resource; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct superhyway_device*) ; 
 struct superhyway_device* to_superhyway_device (struct device*) ; 

__attribute__((used)) static void superhyway_device_release(struct device *dev)
{
	struct superhyway_device *sdev = to_superhyway_device(dev);

	kfree(sdev->resource);
	kfree(sdev);
}