#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnode {TYPE_1__* v_fifoinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  fi_readsock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIONREAD ; 
 int sock_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
fifo_charcount(struct vnode *vp, int *count) 
{
	int mcount;
	int err = sock_ioctl(vp->v_fifoinfo->fi_readsock, FIONREAD, (void*)&mcount);
	if (err == 0) {
		*count = mcount;
	}
	return err;
}