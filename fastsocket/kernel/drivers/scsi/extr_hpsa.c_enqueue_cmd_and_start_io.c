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
struct ctlr_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  Qdepth; int /*<<< orphan*/  reqQ; } ;
struct CommandList {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  addQ (int /*<<< orphan*/ *,struct CommandList*) ; 
 int /*<<< orphan*/  dial_down_lockup_detection_during_fw_flash (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  set_performant_mode (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_io (struct ctlr_info*) ; 

__attribute__((used)) static void enqueue_cmd_and_start_io(struct ctlr_info *h,
	struct CommandList *c)
{
	unsigned long flags;

	set_performant_mode(h, c);
	dial_down_lockup_detection_during_fw_flash(h, c);
	spin_lock_irqsave(&h->lock, flags);
	addQ(&h->reqQ, c);
	h->Qdepth++;
	spin_unlock_irqrestore(&h->lock, flags);
	start_io(h);
}