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
typedef  int /*<<< orphan*/  secure_kern ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int /*<<< orphan*/  sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_secure_kernel(void)
{
	int secure_kern = 0;
	size_t secure_kern_size = sizeof(secure_kern);

	T_ASSERT_POSIX_SUCCESS(sysctlbyname("kern.secure_kernel", &secure_kern,
			&secure_kern_size, NULL, 0), NULL);

	if (secure_kern) {
		T_SKIP("secure kernel: processor_set_tasks will not return kernel_task");
	}
}