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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_KDEBUG ; 
 int KERN_KDSETBUF ; 
 int /*<<< orphan*/  T_FAIL (char*) ; 
 scalar_t__ sysctl (int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _sysctl_setbuf(uint32_t capacity) {
	int mib[] = { CTL_KERN, KERN_KDEBUG, KERN_KDSETBUF, (int)capacity };
	if (sysctl(mib, 4, NULL, NULL, NULL, 0)) {
		T_FAIL("KERN_KDSETBUF sysctl failed");
	}
}