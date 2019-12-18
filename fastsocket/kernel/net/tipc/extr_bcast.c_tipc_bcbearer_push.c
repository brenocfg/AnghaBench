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
struct TYPE_3__ {scalar_t__ blocked; } ;
struct bearer {TYPE_1__ publ; } ;
struct TYPE_4__ {struct bearer bearer; } ;

/* Variables and functions */
 int /*<<< orphan*/  bc_lock ; 
 TYPE_2__* bcbearer ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_bearer_lock_push (struct bearer*) ; 

void tipc_bcbearer_push(void)
{
	struct bearer *b_ptr;

	spin_lock_bh(&bc_lock);
	b_ptr = &bcbearer->bearer;
	if (b_ptr->publ.blocked) {
		b_ptr->publ.blocked = 0;
		tipc_bearer_lock_push(b_ptr);
	}
	spin_unlock_bh(&bc_lock);
}