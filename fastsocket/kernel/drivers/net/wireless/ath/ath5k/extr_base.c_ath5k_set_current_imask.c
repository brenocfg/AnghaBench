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
struct ath5k_hw {int imask; int /*<<< orphan*/  irqlock; scalar_t__ tx_pending; scalar_t__ rx_pending; } ;
typedef  enum ath5k_int { ____Placeholder_ath5k_int } ath5k_int ;

/* Variables and functions */
 int AR5K_INT_RX_ALL ; 
 int AR5K_INT_TX_ALL ; 
 int /*<<< orphan*/  ath5k_hw_set_imr (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ath5k_set_current_imask(struct ath5k_hw *ah)
{
	enum ath5k_int imask;
	unsigned long flags;

	spin_lock_irqsave(&ah->irqlock, flags);
	imask = ah->imask;
	if (ah->rx_pending)
		imask &= ~AR5K_INT_RX_ALL;
	if (ah->tx_pending)
		imask &= ~AR5K_INT_TX_ALL;
	ath5k_hw_set_imr(ah, imask);
	spin_unlock_irqrestore(&ah->irqlock, flags);
}