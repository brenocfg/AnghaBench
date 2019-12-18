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
typedef  int /*<<< orphan*/  enabled ;

/* Variables and functions */
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_exc_resource_threads_enabled()
{
	int err;
	int enabled;
	size_t enabled_size = sizeof(enabled);
	err = sysctlbyname("kern.exc_resource_threads_enabled", &enabled, &enabled_size, NULL, 0);

	if (err || !enabled)
		T_SKIP("EXC_RESOURCE RESOURCE_TYPE_THREADS not enabled on this system");

}