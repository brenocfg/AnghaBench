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
 int ENOMEM ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int platform_device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ *) ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sony_pf_device ; 
 int /*<<< orphan*/  sony_pf_driver ; 
 int /*<<< orphan*/  sony_pf_users ; 

__attribute__((used)) static int sony_pf_add(void)
{
	int ret = 0;

	/* don't run again if already initialized */
	if (atomic_add_return(1, &sony_pf_users) > 1)
		return 0;

	ret = platform_driver_register(&sony_pf_driver);
	if (ret)
		goto out;

	sony_pf_device = platform_device_alloc("sony-laptop", -1);
	if (!sony_pf_device) {
		ret = -ENOMEM;
		goto out_platform_registered;
	}

	ret = platform_device_add(sony_pf_device);
	if (ret)
		goto out_platform_alloced;

	return 0;

      out_platform_alloced:
	platform_device_put(sony_pf_device);
	sony_pf_device = NULL;
      out_platform_registered:
	platform_driver_unregister(&sony_pf_driver);
      out:
	atomic_dec(&sony_pf_users);
	return ret;
}