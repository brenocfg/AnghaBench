#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  aio_workq_entry ;
struct TYPE_5__ {int /*<<< orphan*/  aio_done_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_aio_total_count; int /*<<< orphan*/  p_aio_doneq; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ aio_anchor ; 
 int /*<<< orphan*/  aio_decrement_total_count () ; 
 int /*<<< orphan*/  aio_proc_link ; 

__attribute__((used)) static void
aio_proc_remove_done_locked(proc_t procp, aio_workq_entry *entryp)
{
	TAILQ_REMOVE(&procp->p_aio_doneq, entryp, aio_proc_link);
	OSDecrementAtomic(&aio_anchor.aio_done_count);
	aio_decrement_total_count();
	procp->p_aio_total_count--;
}