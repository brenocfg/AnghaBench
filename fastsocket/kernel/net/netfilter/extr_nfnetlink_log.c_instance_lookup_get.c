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
typedef  int /*<<< orphan*/  u_int16_t ;
struct nfulnl_instance {int dummy; } ;

/* Variables and functions */
 struct nfulnl_instance* __instance_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instance_get (struct nfulnl_instance*) ; 
 int /*<<< orphan*/  instances_lock ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfulnl_instance *
instance_lookup_get(u_int16_t group_num)
{
	struct nfulnl_instance *inst;

	read_lock_bh(&instances_lock);
	inst = __instance_lookup(group_num);
	if (inst)
		instance_get(inst);
	read_unlock_bh(&instances_lock);

	return inst;
}