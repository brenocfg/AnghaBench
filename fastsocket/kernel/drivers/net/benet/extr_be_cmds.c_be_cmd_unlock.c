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
struct be_adapter {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 void mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ use_mcc (struct be_adapter*) ; 

__attribute__((used)) static void be_cmd_unlock(struct be_adapter *adapter)
{
	if (use_mcc(adapter))
		spin_unlock_bh(&adapter->mcc_lock);
	else
		return mutex_unlock(&adapter->mbox_lock);
}