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
struct device {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; void* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dummy_release ; 
 int /*<<< orphan*/  soc_camera_bus_type ; 

__attribute__((used)) static void soc_camera_device_init(struct device *dev, void *pdata)
{
	dev->platform_data	= pdata;
	dev->bus		= &soc_camera_bus_type;
	dev->release		= dummy_release;
}