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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct bearer {TYPE_1__ publ; } ;

/* Variables and functions */
 int bearer_push (struct bearer*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_bcbearer_push () ; 

void tipc_bearer_lock_push(struct bearer *b_ptr)
{
	int res;

	spin_lock_bh(&b_ptr->publ.lock);
	res = bearer_push(b_ptr);
	spin_unlock_bh(&b_ptr->publ.lock);
	if (res)
		tipc_bcbearer_push();
}