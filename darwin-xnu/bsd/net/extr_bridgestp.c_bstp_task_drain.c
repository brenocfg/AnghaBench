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
struct bstp_task {scalar_t__ bt_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  bstp_task_mtx ; 
 int /*<<< orphan*/  bstp_task_queue ; 
 struct bstp_task* bstp_task_queue_running ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct bstp_task**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bstp_task_drain(struct bstp_task *bt)
{
	lck_mtx_lock(bstp_task_mtx);

	while (bt->bt_count != 0 || bstp_task_queue_running == bt) {
		wakeup(&bstp_task_queue);
		msleep(&bstp_task_queue_running, bstp_task_mtx, PZERO, "bstp_task_queue", NULL);
	}
	lck_mtx_unlock(bstp_task_mtx);
}