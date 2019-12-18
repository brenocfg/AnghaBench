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
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CRED () ; 
 int fasttrap_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ proc_is64bit (struct proc*) ; 

__attribute__((used)) static int
_fasttrap_ioctl(dev_t dev, u_long cmd, caddr_t data, int fflag, struct proc *p)
{
	int err, rv = 0;
    user_addr_t uaddrp;

    if (proc_is64bit(p))
        uaddrp = *(user_addr_t *)data;
    else
        uaddrp = (user_addr_t) *(uint32_t *)data;

	err = fasttrap_ioctl(dev, cmd, uaddrp, fflag, CRED(), &rv);

	/* XXX Darwin's BSD ioctls only return -1 or zero. Overload errno to mimic Solaris. 20 bits suffice. */
	if (err != 0) {
		ASSERT( (err & 0xfffff000) == 0 );
		return (err & 0xfff); /* ioctl returns -1 and errno set to an error code < 4096 */
	} else if (rv != 0) {
		ASSERT( (rv & 0xfff00000) == 0 );
		return (((rv & 0xfffff) << 12)); /* ioctl returns -1 and errno set to a return value >= 4096 */
	} else 
		return 0;
}