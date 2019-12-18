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
struct vnop_ioctl_args {int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int EBADF ; 
 int VCALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnop_ioctl_args*) ; 
 int /*<<< orphan*/  VOFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chkvnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnop_ioctl ; 

int
dead_ioctl(struct vnop_ioctl_args *ap)
{

	if (!chkvnlock(ap->a_vp))
		return (EBADF);
	return (VCALL(ap->a_vp, VOFFSET(vnop_ioctl), ap));
}