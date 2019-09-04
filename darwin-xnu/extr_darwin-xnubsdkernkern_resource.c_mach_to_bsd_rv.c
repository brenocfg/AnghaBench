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

/* Variables and functions */
 int EINVAL ; 
#define  KERN_INVALID_ARGUMENT 129 
#define  KERN_SUCCESS 128 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
mach_to_bsd_rv(int mach_rv)
{
	int bsd_rv = 0;

	switch (mach_rv) {
	case KERN_SUCCESS:
		bsd_rv = 0;
		break;
	case KERN_INVALID_ARGUMENT:
		bsd_rv = EINVAL;
		break;
	default:
		panic("unknown error %#x", mach_rv);
	}

	return bsd_rv;
}