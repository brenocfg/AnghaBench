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
struct nfulnl_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __instance_destroy (struct nfulnl_instance*) ; 
 int /*<<< orphan*/  instances_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
instance_destroy(struct nfulnl_instance *inst)
{
	write_lock_bh(&instances_lock);
	__instance_destroy(inst);
	write_unlock_bh(&instances_lock);
}