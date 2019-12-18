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
typedef  int /*<<< orphan*/  u64 ;
struct _sas_node {int /*<<< orphan*/  list; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_node_lock; scalar_t__ shost_recovery; } ;

/* Variables and functions */
 int /*<<< orphan*/  _scsih_expander_node_remove (struct MPT3SAS_ADAPTER*,struct _sas_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct _sas_node* mpt3sas_scsih_expander_find_by_sas_address (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
mpt3sas_expander_remove(struct MPT3SAS_ADAPTER *ioc, u64 sas_address)
{
	struct _sas_node *sas_expander;
	unsigned long flags;

	if (ioc->shost_recovery)
		return;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	sas_expander = mpt3sas_scsih_expander_find_by_sas_address(ioc,
	    sas_address);
	if (sas_expander)
		list_del(&sas_expander->list);
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
	if (sas_expander)
		_scsih_expander_node_remove(ioc, sas_expander);
}