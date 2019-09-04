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
typedef  int /*<<< orphan*/  supported ;

/* Variables and functions */
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
skip_if_unsupported(void)
{
	int r;
	int supported = 0;
	size_t supported_size = sizeof(supported);

	r = sysctlbyname("kern.monotonic.supported", &supported, &supported_size,
			NULL, 0);
	if (r < 0) {
		T_WITH_ERRNO;
		T_SKIP("could not find \"kern.monotonic.supported\" sysctl");
	}

	if (!supported) {
		T_SKIP("monotonic is not supported on this platform");
	}
}