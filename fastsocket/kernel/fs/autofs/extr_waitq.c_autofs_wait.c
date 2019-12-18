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
struct qstr {scalar_t__ len; scalar_t__ hash; int /*<<< orphan*/  name; } ;
struct autofs_wait_queue {scalar_t__ hash; scalar_t__ len; int status; int wait_ctr; int /*<<< orphan*/  queue; struct autofs_wait_queue* name; struct autofs_wait_queue* next; scalar_t__ wait_queue_token; } ;
struct autofs_sb_info {scalar_t__ catatonic; struct autofs_wait_queue* queues; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int EINTR ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NAME_MAX ; 
 int /*<<< orphan*/  SHUTDOWN_SIGS ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  autofs_next_wait_queue ; 
 int /*<<< orphan*/  autofs_notify_daemon (struct autofs_sb_info*,struct autofs_wait_queue*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct autofs_wait_queue*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (struct autofs_wait_queue*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct autofs_wait_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  siginitsetinv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int autofs_wait(struct autofs_sb_info *sbi, struct qstr *name)
{
	struct autofs_wait_queue *wq;
	int status;

	/* In catatonic mode, we don't wait for nobody */
	if ( sbi->catatonic )
		return -ENOENT;
	
	/* We shouldn't be able to get here, but just in case */
	if ( name->len > NAME_MAX )
		return -ENOENT;

	for ( wq = sbi->queues ; wq ; wq = wq->next ) {
		if ( wq->hash == name->hash &&
		     wq->len == name->len &&
		     wq->name && !memcmp(wq->name,name->name,name->len) )
			break;
	}
	
	if ( !wq ) {
		/* Create a new wait queue */
		wq = kmalloc(sizeof(struct autofs_wait_queue),GFP_KERNEL);
		if ( !wq )
			return -ENOMEM;

		wq->name = kmalloc(name->len,GFP_KERNEL);
		if ( !wq->name ) {
			kfree(wq);
			return -ENOMEM;
		}
		wq->wait_queue_token = autofs_next_wait_queue++;
		init_waitqueue_head(&wq->queue);
		wq->hash = name->hash;
		wq->len = name->len;
		wq->status = -EINTR; /* Status return if interrupted */
		memcpy(wq->name, name->name, name->len);
		wq->next = sbi->queues;
		sbi->queues = wq;

		/* autofs_notify_daemon() may block */
		wq->wait_ctr = 2;
		autofs_notify_daemon(sbi,wq);
	} else
		wq->wait_ctr++;

	/* wq->name is NULL if and only if the lock is already released */

	if ( sbi->catatonic ) {
		/* We might have slept, so check again for catatonic mode */
		wq->status = -ENOENT;
		kfree(wq->name);
		wq->name = NULL;
	}

	if ( wq->name ) {
		/* Block all but "shutdown" signals while waiting */
		sigset_t sigmask;

		siginitsetinv(&sigmask, SHUTDOWN_SIGS);
		sigprocmask(SIG_BLOCK, &sigmask, &sigmask);

		interruptible_sleep_on(&wq->queue);

		sigprocmask(SIG_SETMASK, &sigmask, NULL);
	} else {
		DPRINTK(("autofs_wait: skipped sleeping\n"));
	}

	status = wq->status;

	if ( ! --wq->wait_ctr )	/* Are we the last process to need status? */
		kfree(wq);

	return status;
}