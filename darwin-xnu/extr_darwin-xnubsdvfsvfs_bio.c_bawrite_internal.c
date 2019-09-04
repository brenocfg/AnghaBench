#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  TYPE_2__* buf_t ;
struct TYPE_7__ {int /*<<< orphan*/  b_flags; TYPE_1__* b_vp; } ;
struct TYPE_6__ {scalar_t__ v_numoutput; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_ASYNC ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VNODE_ASYNC_THROTTLE ; 
 int VNOP_BWRITE (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_waitforwrites (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
bawrite_internal(buf_t bp, int throttle)
{
	vnode_t	vp = bp->b_vp;

	if (vp) {
	        if (throttle)
		        /*
			 * If the vnode has "too many" write operations in progress
			 * wait for them to finish the IO
			 */
		        (void)vnode_waitforwrites(vp, VNODE_ASYNC_THROTTLE, 0, 0, (const char *)"buf_bawrite");
		else if (vp->v_numoutput >= VNODE_ASYNC_THROTTLE)
		        /*
			 * return to the caller and 
			 * let him decide what to do
			 */
		        return (EWOULDBLOCK);
	}
	SET(bp->b_flags, B_ASYNC);

	return (VNOP_BWRITE(bp));
}