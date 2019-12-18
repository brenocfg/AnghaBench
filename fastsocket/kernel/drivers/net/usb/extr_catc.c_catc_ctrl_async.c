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
typedef  void* u8 ;
typedef  void* u16 ;
struct ctrl_queue {int len; void (* callback ) (struct catc*,struct ctrl_queue*) ;void* buf; void* index; void* value; void* request; void* dir; } ;
struct catc {int ctrl_head; int ctrl_tail; int /*<<< orphan*/  ctrl_lock; int /*<<< orphan*/  flags; struct ctrl_queue* ctrl_queue; } ;

/* Variables and functions */
 int CTRL_QUEUE ; 
 int /*<<< orphan*/  CTRL_RUNNING ; 
 int /*<<< orphan*/  catc_ctrl_run (struct catc*) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int catc_ctrl_async(struct catc *catc, u8 dir, u8 request, u16 value,
	u16 index, void *buf, int len, void (*callback)(struct catc *catc, struct ctrl_queue *q))
{
	struct ctrl_queue *q;
	int retval = 0;
	unsigned long flags;

	spin_lock_irqsave(&catc->ctrl_lock, flags);
	
	q = catc->ctrl_queue + catc->ctrl_head;

	q->dir = dir;
	q->request = request;
	q->value = value;
	q->index = index;
	q->buf = buf;
	q->len = len;
	q->callback = callback;

	catc->ctrl_head = (catc->ctrl_head + 1) & (CTRL_QUEUE - 1);

	if (catc->ctrl_head == catc->ctrl_tail) {
		err("ctrl queue full");
		catc->ctrl_tail = (catc->ctrl_tail + 1) & (CTRL_QUEUE - 1);
		retval = -1;
	}

	if (!test_and_set_bit(CTRL_RUNNING, &catc->flags))
		catc_ctrl_run(catc);

	spin_unlock_irqrestore(&catc->ctrl_lock, flags);

	return retval;
}