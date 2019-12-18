#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {int /*<<< orphan*/  egress_lock; TYPE_1__* eg_cache; } ;
struct atm_vcc {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  use; struct atm_vcc* shortcut; } ;
typedef  TYPE_1__ eg_cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static eg_cache_entry *eg_cache_get_by_vcc(struct atm_vcc *vcc, struct mpoa_client *mpc)
{
	unsigned long flags;
	eg_cache_entry *entry;

	read_lock_irqsave(&mpc->egress_lock, flags);
	entry = mpc->eg_cache;
	while (entry != NULL){
		if (entry->shortcut == vcc) {
			atomic_inc(&entry->use);
			read_unlock_irqrestore(&mpc->egress_lock, flags);
			return entry;
		}
		entry = entry->next;
	}
	read_unlock_irqrestore(&mpc->egress_lock, flags);

	return NULL;
}