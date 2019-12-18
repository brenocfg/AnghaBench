#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int rearm_cq; TYPE_1__ cq; } ;
struct be_adapter {int /*<<< orphan*/  mcc_cq_lock; TYPE_2__ mcc_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cq_notify (struct be_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void be_async_mcc_disable(struct be_adapter *adapter)
{
	spin_lock_bh(&adapter->mcc_cq_lock);

	adapter->mcc_obj.rearm_cq = false;
	be_cq_notify(adapter, adapter->mcc_obj.cq.id, false, 0);

	spin_unlock_bh(&adapter->mcc_cq_lock);
}