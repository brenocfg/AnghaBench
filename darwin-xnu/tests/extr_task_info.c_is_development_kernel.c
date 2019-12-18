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

/* Variables and functions */
 int NOTSET ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_development_kernel(void)
{
#define NOTSET -1

	static int is_dev = NOTSET;

	if (is_dev == NOTSET) {
		int dev;
		size_t dev_size = sizeof(dev);

		T_QUIET;
		T_ASSERT_POSIX_SUCCESS(sysctlbyname("kern.development", &dev, &dev_size, NULL, 0), NULL);
		is_dev = (dev != 0);

		return is_dev;
	} else {
		return is_dev;
	}
#undef NOTSET
}