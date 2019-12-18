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
struct packet_type {scalar_t__ type; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ALL ; 
 int PTYPE_HASH_MASK ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  ptype_all ; 
 int /*<<< orphan*/ * ptype_base ; 
 int /*<<< orphan*/  ptype_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void dev_add_pack(struct packet_type *pt)
{
	int hash;

	spin_lock_bh(&ptype_lock);
	if (pt->type == htons(ETH_P_ALL))
		list_add_rcu(&pt->list, &ptype_all);
	else {
		hash = ntohs(pt->type) & PTYPE_HASH_MASK;
		list_add_rcu(&pt->list, &ptype_base[hash]);
	}
	spin_unlock_bh(&ptype_lock);
}