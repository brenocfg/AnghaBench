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
struct msn_entry {struct msn_entry* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct msn_entry* msn_list; } ;
typedef  TYPE_1__ act2000_card ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct msn_entry*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
act2000_clear_msn(act2000_card *card)
{
	struct msn_entry *p = card->msn_list;
	struct msn_entry *q;
	unsigned long flags;

	spin_lock_irqsave(&card->lock, flags);
	card->msn_list = NULL;
	spin_unlock_irqrestore(&card->lock, flags);
	while (p) {
		q  = p->next;
		kfree(p);
		p = q;
	}
}