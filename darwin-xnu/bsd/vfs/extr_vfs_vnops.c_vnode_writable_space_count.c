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
typedef  int /*<<< orphan*/  vnode_t ;

/* Variables and functions */
 int fifo_freespace (int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vnode_isfifo (int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static intptr_t
vnode_writable_space_count(vnode_t vp) 
{
	if (vnode_isfifo(vp)) {
#if FIFO
		long spc;
		int err = fifo_freespace(vp, &spc);
		if (err == 0) {
			return (intptr_t)spc;
		} else 
#endif
		{
			return (intptr_t)0;
		}
	} else if (vnode_isreg(vp)) {
		return (intptr_t)1;
	} else {
		panic("Should never have an EVFILT_READ except for reg or fifo.");
		return 0;
	}
}