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
typedef  int /*<<< orphan*/  daddr64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 struct bufhashhdr* BUFHASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  buf_mtxp ; 
 scalar_t__ incore_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufhashhdr*) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
incore(vnode_t vp, daddr64_t blkno)
{
        boolean_t retval;
	struct	bufhashhdr *dp;

	dp = BUFHASH(vp, blkno);

	lck_mtx_lock_spin(buf_mtxp);

	if (incore_locked(vp, blkno, dp))
	        retval = TRUE;
	else
	        retval = FALSE;
	lck_mtx_unlock(buf_mtxp);

	return (retval);
}