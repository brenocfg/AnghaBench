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
struct procdata {scalar_t__ if_used; int /*<<< orphan*/  rd_queue; int /*<<< orphan*/  del_lock; struct log_data* log_head; struct log_data* log_tail; } ;
struct log_data {scalar_t__ usage_cnt; struct log_data* next; struct procdata* proc_ctrl; int /*<<< orphan*/  log_start; } ;
struct TYPE_3__ {int /*<<< orphan*/  hysdn_lock; struct procdata* proclog; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct log_data*) ; 
 struct log_data* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
put_log_buffer(hysdn_card * card, char *cp)
{
	struct log_data *ib;
	struct procdata *pd = card->proclog;
	int i;
	unsigned long flags;

	if (!pd)
		return;
	if (!cp)
		return;
	if (!*cp)
		return;
	if (pd->if_used <= 0)
		return;		/* no open file for read */

	if (!(ib = kmalloc(sizeof(struct log_data) + strlen(cp), GFP_ATOMIC)))
		 return;	/* no memory */
	strcpy(ib->log_start, cp);	/* set output string */
	ib->next = NULL;
	ib->proc_ctrl = pd;	/* point to own control structure */
	spin_lock_irqsave(&card->hysdn_lock, flags);
	ib->usage_cnt = pd->if_used;
	if (!pd->log_head)
		pd->log_head = ib;	/* new head */
	else
		pd->log_tail->next = ib;	/* follows existing messages */
	pd->log_tail = ib;	/* new tail */
	i = pd->del_lock++;	/* get lock state */
	spin_unlock_irqrestore(&card->hysdn_lock, flags);

	/* delete old entrys */
	if (!i)
		while (pd->log_head->next) {
			if ((pd->log_head->usage_cnt <= 0) &&
			    (pd->log_head->next->usage_cnt <= 0)) {
				ib = pd->log_head;
				pd->log_head = pd->log_head->next;
				kfree(ib);
			} else
				break;
		}		/* pd->log_head->next */
	pd->del_lock--;		/* release lock level */
	wake_up_interruptible(&(pd->rd_queue));		/* announce new entry */
}