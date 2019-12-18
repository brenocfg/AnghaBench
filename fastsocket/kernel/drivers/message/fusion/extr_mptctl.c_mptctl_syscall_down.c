#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_1__ ioctl_cmds; } ;
typedef  TYPE_2__ MPT_ADAPTER ;

/* Variables and functions */
 int EAGAIN ; 
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
mptctl_syscall_down(MPT_ADAPTER *ioc, int nonblock)
{
	int rc = 0;

	if (nonblock) {
		if (!mutex_trylock(&ioc->ioctl_cmds.mutex))
			rc = -EAGAIN;
	} else {
		if (mutex_lock_interruptible(&ioc->ioctl_cmds.mutex))
			rc = -ERESTARTSYS;
	}
	return rc;
}