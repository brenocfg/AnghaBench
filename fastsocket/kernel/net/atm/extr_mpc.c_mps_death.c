#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {TYPE_2__* eg_ops; TYPE_1__* in_ops; int /*<<< orphan*/  egress_lock; TYPE_4__* eg_cache; TYPE_3__* dev; int /*<<< orphan*/  mps_ctrl_addr; } ;
struct k_message {int /*<<< orphan*/  MPS_ctrl; } ;
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/  shortcut; } ;
typedef  TYPE_4__ eg_cache_entry ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* destroy_cache ) (struct mpoa_client*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy_cache ) (struct mpoa_client*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_ESA_LEN ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  purge_egress_shortcut (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  read_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mpoa_client*) ; 
 int /*<<< orphan*/  stub2 (struct mpoa_client*) ; 

__attribute__((used)) static void mps_death( struct k_message * msg, struct mpoa_client * mpc )
{
	eg_cache_entry *entry;

	dprintk("mpoa: (%s) mps_death:\n", mpc->dev->name);

	if(memcmp(msg->MPS_ctrl, mpc->mps_ctrl_addr, ATM_ESA_LEN)){
		printk("mpoa: (%s) mps_death: wrong MPS\n", mpc->dev->name);
		return;
	}

	/* FIXME: This knows too much of the cache structure */
	read_lock_irq(&mpc->egress_lock);
	entry = mpc->eg_cache;
	while (entry != NULL) {
		purge_egress_shortcut(entry->shortcut, entry);
		entry = entry->next;
	}
	read_unlock_irq(&mpc->egress_lock);

	mpc->in_ops->destroy_cache(mpc);
	mpc->eg_ops->destroy_cache(mpc);

	return;
}