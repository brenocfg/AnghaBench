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
struct nilfs_segctor_wait_request {int err; int /*<<< orphan*/  wq; int /*<<< orphan*/  done; scalar_t__ seq; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_wait_request; int /*<<< orphan*/  sc_wait_daemon; int /*<<< orphan*/  sc_state_lock; scalar_t__ sc_seq_request; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_segctor_sync(struct nilfs_sc_info *sci)
{
	struct nilfs_segctor_wait_request wait_req;
	int err = 0;

	spin_lock(&sci->sc_state_lock);
	init_wait(&wait_req.wq);
	wait_req.err = 0;
	atomic_set(&wait_req.done, 0);
	wait_req.seq = ++sci->sc_seq_request;
	spin_unlock(&sci->sc_state_lock);

	init_waitqueue_entry(&wait_req.wq, current);
	add_wait_queue(&sci->sc_wait_request, &wait_req.wq);
	set_current_state(TASK_INTERRUPTIBLE);
	wake_up(&sci->sc_wait_daemon);

	for (;;) {
		if (atomic_read(&wait_req.done)) {
			err = wait_req.err;
			break;
		}
		if (!signal_pending(current)) {
			schedule();
			continue;
		}
		err = -ERESTARTSYS;
		break;
	}
	finish_wait(&sci->sc_wait_request, &wait_req.wq);
	return err;
}