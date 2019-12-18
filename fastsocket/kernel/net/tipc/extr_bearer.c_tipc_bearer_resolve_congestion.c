#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct link {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct bearer {TYPE_1__ publ; int /*<<< orphan*/  cong_links; } ;

/* Variables and functions */
 int /*<<< orphan*/  bearer_push (struct bearer*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_bearer_schedule_unlocked (struct bearer*,struct link*) ; 

int tipc_bearer_resolve_congestion(struct bearer *b_ptr, struct link *l_ptr)
{
	int res = 1;

	if (list_empty(&b_ptr->cong_links))
		return 1;
	spin_lock_bh(&b_ptr->publ.lock);
	if (!bearer_push(b_ptr)) {
		tipc_bearer_schedule_unlocked(b_ptr, l_ptr);
		res = 0;
	}
	spin_unlock_bh(&b_ptr->publ.lock);
	return res;
}