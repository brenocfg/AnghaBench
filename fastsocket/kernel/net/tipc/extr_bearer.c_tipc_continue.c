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
struct tipc_bearer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ blocked; } ;
struct bearer {TYPE_1__ publ; int /*<<< orphan*/  cong_links; int /*<<< orphan*/  continue_count; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ tipc_bearer_lock_push ; 
 int /*<<< orphan*/  tipc_k_signal (int /*<<< orphan*/ ,unsigned long) ; 

void tipc_continue(struct tipc_bearer *tb_ptr)
{
	struct bearer *b_ptr = (struct bearer *)tb_ptr;

	spin_lock_bh(&b_ptr->publ.lock);
	b_ptr->continue_count++;
	if (!list_empty(&b_ptr->cong_links))
		tipc_k_signal((Handler)tipc_bearer_lock_push, (unsigned long)b_ptr);
	b_ptr->publ.blocked = 0;
	spin_unlock_bh(&b_ptr->publ.lock);
}