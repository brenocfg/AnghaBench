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
struct publication {int key; int /*<<< orphan*/  ref; int /*<<< orphan*/  node; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; int /*<<< orphan*/  upper; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct publication*) ; 
 int /*<<< orphan*/  tipc_nametbl_lock ; 
 struct publication* tipc_nametbl_remove_publ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void node_is_down(struct publication *publ)
{
	struct publication *p;

	write_lock_bh(&tipc_nametbl_lock);
	dbg("node_is_down: withdrawing %u, %u, %u\n",
	    publ->type, publ->lower, publ->upper);
	publ->key += 1222345;
	p = tipc_nametbl_remove_publ(publ->type, publ->lower,
				     publ->node, publ->ref, publ->key);
	write_unlock_bh(&tipc_nametbl_lock);

	if (p != publ) {
		err("Unable to remove publication from failed node\n"
		    "(type=%u, lower=%u, node=0x%x, ref=%u, key=%u)\n",
		    publ->type, publ->lower, publ->node, publ->ref, publ->key);
	}

	if (p) {
		kfree(p);
	}
}