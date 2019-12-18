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
struct divert_info {scalar_t__ usage_cnt; struct divert_info* next; int /*<<< orphan*/  info_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct divert_info* divert_info_head ; 
 int /*<<< orphan*/  divert_info_lock ; 
 struct divert_info* divert_info_tail ; 
 scalar_t__ if_used ; 
 int /*<<< orphan*/  kfree (struct divert_info*) ; 
 struct divert_info* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd_queue ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void
put_info_buffer(char *cp)
{
	struct divert_info *ib;
	unsigned long flags;

	if (if_used <= 0)
		return;
	if (!cp)
		return;
	if (!*cp)
		return;
	if (!(ib = kmalloc(sizeof(struct divert_info) + strlen(cp), GFP_ATOMIC)))
		 return;	/* no memory */
	strcpy(ib->info_start, cp);	/* set output string */
	ib->next = NULL;
	spin_lock_irqsave( &divert_info_lock, flags );
	ib->usage_cnt = if_used;
	if (!divert_info_head)
		divert_info_head = ib;	/* new head */
	else
		divert_info_tail->next = ib;	/* follows existing messages */
	divert_info_tail = ib;	/* new tail */

	/* delete old entrys */
	while (divert_info_head->next) {
		if ((divert_info_head->usage_cnt <= 0) &&
		    (divert_info_head->next->usage_cnt <= 0)) {
			ib = divert_info_head;
			divert_info_head = divert_info_head->next;
			kfree(ib);
		} else
			break;
	}			/* divert_info_head->next */
	spin_unlock_irqrestore( &divert_info_lock, flags );
	wake_up_interruptible(&(rd_queue));
}