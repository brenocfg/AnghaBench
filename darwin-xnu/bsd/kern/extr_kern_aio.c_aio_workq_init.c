#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* aio_workq_t ;
struct TYPE_3__ {int /*<<< orphan*/  aioq_waitq; int /*<<< orphan*/  aioq_mtx; scalar_t__ aioq_count; int /*<<< orphan*/  aioq_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_POLICY_FIFO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aio_lock_attr ; 
 int /*<<< orphan*/  aio_queue_lock_grp ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
aio_workq_init(aio_workq_t wq)
{
	TAILQ_INIT(&wq->aioq_entries);
	wq->aioq_count = 0;
	lck_mtx_init(&wq->aioq_mtx, aio_queue_lock_grp, aio_lock_attr);
	waitq_init(&wq->aioq_waitq, SYNC_POLICY_FIFO);
}