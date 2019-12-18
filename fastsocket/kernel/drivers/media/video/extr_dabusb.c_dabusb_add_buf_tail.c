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
struct list_head {struct list_head* next; } ;
typedef  TYPE_1__* pdabusb_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dabusb_add_buf_tail (pdabusb_t s, struct list_head *dst, struct list_head *src)
{
	unsigned long flags;
	struct list_head *tmp;
	int ret = 0;

	spin_lock_irqsave (&s->lock, flags);

	if (list_empty (src)) {
		// no elements in source buffer
		ret = -1;
		goto err;
	}
	tmp = src->next;
	list_move_tail (tmp, dst);

  err:	spin_unlock_irqrestore (&s->lock, flags);
	return ret;
}