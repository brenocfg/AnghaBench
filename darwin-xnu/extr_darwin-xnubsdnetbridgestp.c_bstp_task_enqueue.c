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
struct bstp_task {int bt_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bstp_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_task_mtx ; 
 int /*<<< orphan*/  bstp_task_queue ; 
 int /*<<< orphan*/  bt_next ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bstp_task_enqueue(struct bstp_task *bt)
{
	lck_mtx_lock(bstp_task_mtx);

	if (bt->bt_count) {
		bt->bt_count++;
		lck_mtx_unlock(bstp_task_mtx);
		wakeup(&bstp_task_queue);
		return;
	}
	
	bt->bt_count = 1;
	TAILQ_INSERT_TAIL(&bstp_task_queue, bt, bt_next);
	
	lck_mtx_unlock(bstp_task_mtx);
	
	wakeup(&bstp_task_queue);
}