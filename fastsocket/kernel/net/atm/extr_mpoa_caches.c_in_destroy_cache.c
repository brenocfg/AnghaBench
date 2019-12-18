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
struct mpoa_client {int /*<<< orphan*/  ingress_lock; int /*<<< orphan*/ * in_cache; TYPE_1__* in_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove_entry ) (int /*<<< orphan*/ *,struct mpoa_client*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct mpoa_client*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void in_destroy_cache(struct mpoa_client *mpc)
{
	write_lock_irq(&mpc->ingress_lock);
	while(mpc->in_cache != NULL)
		mpc->in_ops->remove_entry(mpc->in_cache, mpc);
	write_unlock_irq(&mpc->ingress_lock);

	return;
}