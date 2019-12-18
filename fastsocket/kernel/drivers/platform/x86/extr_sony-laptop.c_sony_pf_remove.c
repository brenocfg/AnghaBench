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
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sony_pf_device ; 
 int /*<<< orphan*/  sony_pf_driver ; 
 int /*<<< orphan*/  sony_pf_users ; 

__attribute__((used)) static void sony_pf_remove(void)
{
	/* deregister only after the last user has gone */
	if (!atomic_dec_and_test(&sony_pf_users))
		return;

	platform_device_del(sony_pf_device);
	platform_device_put(sony_pf_device);
	platform_driver_unregister(&sony_pf_driver);
}