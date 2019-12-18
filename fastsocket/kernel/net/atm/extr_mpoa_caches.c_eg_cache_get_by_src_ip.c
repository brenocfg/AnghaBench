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
struct TYPE_3__ {scalar_t__ latest_ip_addr; struct TYPE_3__* next; int /*<<< orphan*/  use; } ;
typedef  TYPE_1__ eg_cache_entry ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static eg_cache_entry *eg_cache_get_by_src_ip(__be32 ipaddr, struct mpoa_client *mpc)
{
	eg_cache_entry *entry;

	read_lock_irq(&mpc->egress_lock);
	entry = mpc->eg_cache;
	while(entry != NULL){
		if(entry->latest_ip_addr == ipaddr) {
			atomic_inc(&entry->use);
			read_unlock_irq(&mpc->egress_lock);
			return entry;
		}
		entry = entry->next;
	}
	read_unlock_irq(&mpc->egress_lock);

	return NULL;
}