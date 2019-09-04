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
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_KDEBUG ; 
 int KERN_KDTEST ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
assert_kdebug_test(unsigned int flavor)
{
	size_t size = flavor;
	int mib[] = { CTL_KERN, KERN_KDEBUG, KERN_KDTEST };
	T_ASSERT_POSIX_SUCCESS(sysctl(mib, sizeof(mib) / sizeof(mib[0]), NULL,
			&size, NULL, 0), "KERN_KDTEST sysctl");
}