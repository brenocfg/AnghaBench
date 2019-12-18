#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ lck_mtx_tag; int lck_mtx_waiters; TYPE_2__* lck_mtx_ptr; } ;
typedef  TYPE_3__ lck_mtx_t ;
struct TYPE_8__ {int lck_mtx_waiters; } ;
struct TYPE_9__ {TYPE_1__ lck_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ LCK_MTX_TAG_INDIRECT ; 
 int /*<<< orphan*/  lck_mtx_assert (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  lck_mtx_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_yield_no_wait ; 
 int /*<<< orphan*/  mutex_yield_wait ; 

void
lck_mtx_yield(
	    lck_mtx_t	*lck)
{
	int	waiters;
	
#if DEBUG
	lck_mtx_assert(lck, LCK_MTX_ASSERT_OWNED);
#endif /* DEBUG */
	
	if (lck->lck_mtx_tag == LCK_MTX_TAG_INDIRECT)
	        waiters = lck->lck_mtx_ptr->lck_mtx.lck_mtx_waiters;
	else
	        waiters = lck->lck_mtx_waiters;

	if ( !waiters) {
	        mutex_yield_no_wait++;
	} else {
	        mutex_yield_wait++;
		lck_mtx_unlock(lck);
		mutex_pause(0);
		lck_mtx_lock(lck);
	}
}