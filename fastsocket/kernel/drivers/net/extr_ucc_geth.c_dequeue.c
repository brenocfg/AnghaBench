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
struct list_head {struct list_head* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (struct list_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ugeth_lock ; 

__attribute__((used)) static struct list_head *dequeue(struct list_head *lh)
{
	unsigned long flags;

	spin_lock_irqsave(&ugeth_lock, flags);
	if (!list_empty(lh)) {
		struct list_head *node = lh->next;
		list_del(node);
		spin_unlock_irqrestore(&ugeth_lock, flags);
		return node;
	} else {
		spin_unlock_irqrestore(&ugeth_lock, flags);
		return NULL;
	}
}