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
struct list_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  prev; } ;
struct TYPE_4__ {int /*<<< orphan*/  req_lock; TYPE_1__ pending_req_list; } ;

/* Variables and functions */
 TYPE_2__ blizzard ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  list_splice_init (struct list_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_pending_requests () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void submit_req_list(struct list_head *head)
{
	unsigned long flags;
	int process = 1;

	spin_lock_irqsave(&blizzard.req_lock, flags);
	if (likely(!list_empty(&blizzard.pending_req_list)))
		process = 0;
	list_splice_init(head, blizzard.pending_req_list.prev);
	spin_unlock_irqrestore(&blizzard.req_lock, flags);

	if (process)
		process_pending_requests();
}