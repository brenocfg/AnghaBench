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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ tx_state; int /*<<< orphan*/  lock; } ;
struct nvt_dev {TYPE_1__ tx; } ;

/* Variables and functions */
 scalar_t__ ST_TX_NONE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool nvt_cir_tx_inactive(struct nvt_dev *nvt)
{
	unsigned long flags;
	bool tx_inactive;
	u8 tx_state;

	spin_lock_irqsave(&nvt->tx.lock, flags);
	tx_state = nvt->tx.tx_state;
	spin_unlock_irqrestore(&nvt->tx.lock, flags);

	tx_inactive = (tx_state == ST_TX_NONE);

	return tx_inactive;
}