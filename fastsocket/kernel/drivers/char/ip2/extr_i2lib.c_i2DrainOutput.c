#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
typedef  TYPE_1__* i2eBordStrPtr ;
typedef  TYPE_2__* i2ChanStrPtr ;
struct TYPE_12__ {scalar_t__ expires; } ;
struct TYPE_11__ {TYPE_4__ BookmarkTimer; int /*<<< orphan*/  pBookmarkWait; TYPE_1__* pMyBord; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* i2eFatalTrap ) (TYPE_1__*) ;scalar_t__ i2eFatal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANN ; 
 int /*<<< orphan*/  CMD_BMARK_REQ ; 
 int /*<<< orphan*/  ITRC_DRAIN ; 
 int ITRC_ENTER ; 
 int ITRC_RETURN ; 
 int /*<<< orphan*/  PTYPE_INLINE ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  i2DrainWakeup ; 
 int /*<<< orphan*/  i2QueueCommands (int /*<<< orphan*/ ,TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  serviceOutgoingFifo (TYPE_1__*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (TYPE_4__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
i2DrainOutput(i2ChanStrPtr pCh, int timeout)
{
	wait_queue_t wait;
	i2eBordStrPtr pB;

	ip2trace (CHANN, ITRC_DRAIN, ITRC_ENTER, 1, pCh->BookmarkTimer.expires);

	pB = pCh->pMyBord;
	// If the board has gone fatal, return bad, 
	// and also hit the trap routine if it exists.
	if (pB->i2eFatal) {
		if (pB->i2eFatalTrap) {
			(*(pB)->i2eFatalTrap)(pB);
		}
		return;
	}
	if ((timeout > 0) && (pCh->BookmarkTimer.expires == 0 )) {
		// One per customer (channel)
		setup_timer(&pCh->BookmarkTimer, i2DrainWakeup,
				(unsigned long)pCh);

		ip2trace (CHANN, ITRC_DRAIN, 1, 1, pCh->BookmarkTimer.expires );

		mod_timer(&pCh->BookmarkTimer, jiffies + timeout);
	}
	
	i2QueueCommands( PTYPE_INLINE, pCh, -1, 1, CMD_BMARK_REQ );

	init_waitqueue_entry(&wait, current);
	add_wait_queue(&(pCh->pBookmarkWait), &wait);
	set_current_state( TASK_INTERRUPTIBLE );

	serviceOutgoingFifo( pB );
	
	schedule();	// Now we take our interruptible sleep on

	// Clean up the queue
	set_current_state( TASK_RUNNING );
	remove_wait_queue(&(pCh->pBookmarkWait), &wait);

	// if expires == 0 then timer poped, then do not need to del_timer
	if ((timeout > 0) && pCh->BookmarkTimer.expires && 
	                     time_before(jiffies, pCh->BookmarkTimer.expires)) {
		del_timer( &(pCh->BookmarkTimer) );
		pCh->BookmarkTimer.expires = 0;

		ip2trace (CHANN, ITRC_DRAIN, 3, 1, pCh->BookmarkTimer.expires );

	}
	ip2trace (CHANN, ITRC_DRAIN, ITRC_RETURN, 1, pCh->BookmarkTimer.expires );
	return;
}