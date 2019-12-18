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
struct TYPE_2__ {scalar_t__ read_ptr; scalar_t__ write_ptr; } ;
struct iwl_txq {int /*<<< orphan*/  stuck_timer; TYPE_1__ q; } ;
struct iwl_trans_pcie {scalar_t__ wd_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void iwl_pcie_txq_progress(struct iwl_trans_pcie *trans_pcie,
					   struct iwl_txq *txq)
{
	if (!trans_pcie->wd_timeout)
		return;

	/*
	 * if empty delete timer, otherwise move timer forward
	 * since we're making progress on this queue
	 */
	if (txq->q.read_ptr == txq->q.write_ptr)
		del_timer(&txq->stuck_timer);
	else
		mod_timer(&txq->stuck_timer, jiffies + trans_pcie->wd_timeout);
}