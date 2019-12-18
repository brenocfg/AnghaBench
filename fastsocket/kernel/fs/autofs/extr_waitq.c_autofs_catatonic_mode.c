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
struct autofs_wait_queue {int /*<<< orphan*/  queue; int /*<<< orphan*/ * name; int /*<<< orphan*/  status; struct autofs_wait_queue* next; } ;
struct autofs_sb_info {int catatonic; int /*<<< orphan*/  dirhash; int /*<<< orphan*/ * pipe; struct autofs_wait_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  autofs_hash_dputall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void autofs_catatonic_mode(struct autofs_sb_info *sbi)
{
	struct autofs_wait_queue *wq, *nwq;

	DPRINTK(("autofs: entering catatonic mode\n"));

	sbi->catatonic = 1;
	wq = sbi->queues;
	sbi->queues = NULL;	/* Erase all wait queues */
	while ( wq ) {
		nwq = wq->next;
		wq->status = -ENOENT; /* Magic is gone - report failure */
		kfree(wq->name);
		wq->name = NULL;
		wake_up(&wq->queue);
		wq = nwq;
	}
	fput(sbi->pipe);	/* Close the pipe */
	sbi->pipe = NULL;
	autofs_hash_dputall(&sbi->dirhash); /* Remove all dentry pointers */
}