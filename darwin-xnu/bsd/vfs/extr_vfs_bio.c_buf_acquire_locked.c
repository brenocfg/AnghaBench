#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  TYPE_1__* buf_t ;
struct TYPE_4__ {int b_tag; int /*<<< orphan*/  b_owner; int /*<<< orphan*/  b_lflags; int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int BAC_NOWAIT ; 
 int BAC_REMOVE ; 
 int BAC_SKIP_LOCKED ; 
 int BAC_SKIP_NONLOCKED ; 
 int /*<<< orphan*/  BL_BUSY ; 
 int /*<<< orphan*/  BL_WANTED ; 
 int /*<<< orphan*/  B_LOCKED ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EBUSY ; 
 scalar_t__ EDEADLK ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NSEC_PER_USEC ; 
 int PRIBIO ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bremfree_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  buf_busycount ; 
 int /*<<< orphan*/  buf_mtxp ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct timespec*) ; 

__attribute__((used)) static errno_t
buf_acquire_locked(buf_t bp, int flags, int slpflag, int slptimeo)
{
	errno_t error;
	struct timespec ts;

	if (ISSET(bp->b_flags, B_LOCKED)) {
	        if ((flags & BAC_SKIP_LOCKED))
			return (EDEADLK);
	} else {
	        if ((flags & BAC_SKIP_NONLOCKED))
			return (EDEADLK);
	}
        if (ISSET(bp->b_lflags, BL_BUSY)) {
	        /*	
		 * since the lck_mtx_lock may block, the buffer
		 * may become BUSY, so we need to
		 * recheck for a NOWAIT request
		 */
	        if (flags & BAC_NOWAIT)
			return (EBUSY);
	        SET(bp->b_lflags, BL_WANTED);

		/* the hz value is 100; which leads to 10ms */
		ts.tv_sec = (slptimeo/100);
		ts.tv_nsec = (slptimeo % 100) * 10  * NSEC_PER_USEC * 1000;
		error = msleep((caddr_t)bp, buf_mtxp, slpflag | (PRIBIO + 1), "buf_acquire", &ts);

		if (error)
			return (error);
		return (EAGAIN);
	}
	if (flags & BAC_REMOVE)
	        bremfree_locked(bp);
	SET(bp->b_lflags, BL_BUSY);
	buf_busycount++;

#ifdef JOE_DEBUG
	bp->b_owner = current_thread();
	bp->b_tag   = 5;
#endif
	return (0);
}