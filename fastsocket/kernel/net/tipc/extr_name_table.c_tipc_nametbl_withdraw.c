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
typedef  int /*<<< orphan*/  u32 ;
struct publication {scalar_t__ scope; int /*<<< orphan*/  pport_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  local_publ_count; } ;

/* Variables and functions */
 scalar_t__ TIPC_NODE_SCOPE ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct publication*) ; 
 scalar_t__ likely (struct publication*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ table ; 
 int /*<<< orphan*/  tipc_named_withdraw (struct publication*) ; 
 int /*<<< orphan*/  tipc_nametbl_lock ; 
 struct publication* tipc_nametbl_remove_publ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int tipc_nametbl_withdraw(u32 type, u32 lower, u32 ref, u32 key)
{
	struct publication *publ;

	dbg("tipc_nametbl_withdraw: {%u,%u}, key=%u\n", type, lower, key);
	write_lock_bh(&tipc_nametbl_lock);
	publ = tipc_nametbl_remove_publ(type, lower, tipc_own_addr, ref, key);
	if (likely(publ)) {
		table.local_publ_count--;
		if (publ->scope != TIPC_NODE_SCOPE)
			tipc_named_withdraw(publ);
		write_unlock_bh(&tipc_nametbl_lock);
		list_del_init(&publ->pport_list);
		kfree(publ);
		return 1;
	}
	write_unlock_bh(&tipc_nametbl_lock);
	err("Unable to remove local publication\n"
	    "(type=%u, lower=%u, ref=%u, key=%u)\n",
	    type, lower, ref, key);
	return 0;
}