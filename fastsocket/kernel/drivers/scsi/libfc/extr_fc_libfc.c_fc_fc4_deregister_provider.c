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
struct fc4_prov {scalar_t__ recv; } ;
typedef  enum fc_fh_type { ____Placeholder_fc_fh_type } fc_fh_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FC_FC4_PROV_SIZE ; 
 int /*<<< orphan*/ * fc_active_prov ; 
 int /*<<< orphan*/ * fc_passive_prov ; 
 int /*<<< orphan*/  fc_prov_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void fc_fc4_deregister_provider(enum fc_fh_type type, struct fc4_prov *prov)
{
	BUG_ON(type >= FC_FC4_PROV_SIZE);
	mutex_lock(&fc_prov_mutex);
	if (prov->recv)
		rcu_assign_pointer(fc_passive_prov[type], NULL);
	else
		rcu_assign_pointer(fc_active_prov[type], NULL);
	mutex_unlock(&fc_prov_mutex);
	synchronize_rcu();
}