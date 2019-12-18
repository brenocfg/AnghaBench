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
 int /*<<< orphan*/  acerhdf_dev ; 
 int /*<<< orphan*/  acerhdf_driver ; 
 int /*<<< orphan*/  platform_device_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acerhdf_unregister_platform(void)
{
	if (!acerhdf_dev)
		return;

	platform_device_del(acerhdf_dev);
	platform_driver_unregister(&acerhdf_driver);
}