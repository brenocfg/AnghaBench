#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  aio_workq_entry ;
struct TYPE_6__ {int /*<<< orphan*/  aio_done_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_aio_active_count; int /*<<< orphan*/  p_aio_doneq; int /*<<< orphan*/  p_aio_activeq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_AIO_PROC_LOCK_OWNED (TYPE_1__*) ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ aio_anchor ; 
 int /*<<< orphan*/  aio_proc_link ; 

__attribute__((used)) static void
aio_proc_move_done_locked(proc_t procp, aio_workq_entry *entryp)
{
	ASSERT_AIO_PROC_LOCK_OWNED(procp);

	TAILQ_REMOVE(&procp->p_aio_activeq, entryp, aio_proc_link );
	TAILQ_INSERT_TAIL( &procp->p_aio_doneq, entryp, aio_proc_link);
	procp->p_aio_active_count--;
	OSIncrementAtomic(&aio_anchor.aio_done_count);
}