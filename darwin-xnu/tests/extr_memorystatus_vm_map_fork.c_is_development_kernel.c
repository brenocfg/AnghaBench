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
typedef  int /*<<< orphan*/  dev ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
is_development_kernel(void)
{
	int ret;
	int dev = 0;
	size_t dev_size = sizeof(dev);

	ret = sysctlbyname("kern.development", &dev, &dev_size, NULL, 0);
	if (ret != 0) {
		return FALSE;
	}

	return (dev != 0);
}