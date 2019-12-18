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
 int /*<<< orphan*/ * cl_dev ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * thz_dev ; 

__attribute__((used)) static void acerhdf_unregister_thermal(void)
{
	if (cl_dev) {
		thermal_cooling_device_unregister(cl_dev);
		cl_dev = NULL;
	}

	if (thz_dev) {
		thermal_zone_device_unregister(thz_dev);
		thz_dev = NULL;
	}
}