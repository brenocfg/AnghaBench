#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct saa7146_dmaqueue {TYPE_2__* curr; } ;
struct saa7146_dev {int /*<<< orphan*/  slock; } ;
struct TYPE_3__ {int state; int /*<<< orphan*/  done; int /*<<< orphan*/  ts; } ;
struct TYPE_4__ {TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void saa7146_buffer_finish(struct saa7146_dev *dev,
			   struct saa7146_dmaqueue *q,
			   int state)
{
	assert_spin_locked(&dev->slock);
	DEB_EE(("dev:%p, dmaq:%p, state:%d\n", dev, q, state));
	DEB_EE(("q->curr:%p\n",q->curr));

	BUG_ON(!q->curr);

	/* finish current buffer */
	if (NULL == q->curr) {
		DEB_D(("aiii. no current buffer\n"));
		return;
	}

	q->curr->vb.state = state;
	do_gettimeofday(&q->curr->vb.ts);
	wake_up(&q->curr->vb.done);

	q->curr = NULL;
}