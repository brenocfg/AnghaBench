#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ Qdepth; scalar_t__ maxQsinceinit; int /*<<< orphan*/  lock; int /*<<< orphan*/  reqQ; } ;
typedef  TYPE_1__ ctlr_info_t ;
typedef  int /*<<< orphan*/  CommandList_struct ;

/* Variables and functions */
 int /*<<< orphan*/  addQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_performant_mode (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_io (TYPE_1__*) ; 

__attribute__((used)) static void enqueue_cmd_and_start_io(ctlr_info_t *h,
	CommandList_struct *c)
{
	unsigned long flags;

	set_performant_mode(h, c);
	spin_lock_irqsave(&h->lock, flags);
	addQ(&h->reqQ, c);
	h->Qdepth++;
	if (h->Qdepth > h->maxQsinceinit)
		h->maxQsinceinit = h->Qdepth;
	start_io(h);
	spin_unlock_irqrestore(&h->lock, flags);
}