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
typedef  int /*<<< orphan*/  u_long ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int dtrace_ioctl_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
helper_ioctl(dev_t dev, u_long cmd, caddr_t data, int fflag, struct proc *p)
{
#pragma unused(dev,fflag,p)
	int err, rv = 0;
	
	err = dtrace_ioctl_helper(cmd, data, &rv);
	/* Darwin's BSD ioctls only return -1 or zero. Overload errno to mimic Solaris. 20 bits suffice. */
	if (err != 0) {
		ASSERT( (err & 0xfffff000) == 0 );
		return (err & 0xfff); /* ioctl will return -1 and will set errno to an error code < 4096 */
	} else if (rv != 0) {
		ASSERT( (rv & 0xfff00000) == 0 );
		return (((rv & 0xfffff) << 12)); /* ioctl will return -1 and will set errno to a value >= 4096 */
	} else 
		return 0;
}