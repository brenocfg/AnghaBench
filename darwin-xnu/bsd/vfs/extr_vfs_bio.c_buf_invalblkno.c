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
struct bufhashhdr {int dummy; } ;
struct buf {int b_lflags; int b_flags; int b_tag; int /*<<< orphan*/  b_owner; } ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  daddr64_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  struct buf* buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  BL_BUSY ; 
 int /*<<< orphan*/  BL_WANTED ; 
 struct bufhashhdr* BUFHASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUF_WAIT ; 
 int /*<<< orphan*/  B_INVAL ; 
 scalar_t__ EBUSY ; 
 scalar_t__ ISSET (int,int /*<<< orphan*/ ) ; 
 int PDROP ; 
 int PRIBIO ; 
 int /*<<< orphan*/  SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bremfree_locked (struct buf*) ; 
 int /*<<< orphan*/  buf_brelse (struct buf*) ; 
 int /*<<< orphan*/  buf_busycount ; 
 int /*<<< orphan*/  buf_mtxp ; 
 int /*<<< orphan*/  current_thread () ; 
 struct buf* incore_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufhashhdr*) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 

errno_t
buf_invalblkno(vnode_t vp, daddr64_t lblkno, int flags)
{
        buf_t	bp;
	errno_t	error;
	struct bufhashhdr *dp;

	dp = BUFHASH(vp, lblkno);

relook:	
	lck_mtx_lock_spin(buf_mtxp);

	if ((bp = incore_locked(vp, lblkno, dp)) == (struct buf *)0) {
	        lck_mtx_unlock(buf_mtxp);
		return (0);
	}
	if (ISSET(bp->b_lflags, BL_BUSY)) {
	        if ( !ISSET(flags, BUF_WAIT)) {
		        lck_mtx_unlock(buf_mtxp);
			return (EBUSY);
		}
	        SET(bp->b_lflags, BL_WANTED);

		error = msleep((caddr_t)bp, buf_mtxp, PDROP | (PRIBIO + 1), "buf_invalblkno", NULL);

		if (error) {
			return (error);
		}
		goto relook;
	}
	bremfree_locked(bp);
	SET(bp->b_lflags, BL_BUSY);
	SET(bp->b_flags, B_INVAL);
	buf_busycount++;
#ifdef JOE_DEBUG
	bp->b_owner = current_thread();
	bp->b_tag   = 4;
#endif
	lck_mtx_unlock(buf_mtxp);
	buf_brelse(bp);

	return (0);
}