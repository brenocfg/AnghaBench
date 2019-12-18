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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ max_txtrig_level; } ;
struct ath_hw {scalar_t__ tx_trig_level; TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ AR_FTRIG ; 
 int /*<<< orphan*/  AR_TXCFG ; 
 scalar_t__ MIN_TX_FIFO_THRESHOLD ; 
 scalar_t__ MS (scalar_t__,scalar_t__) ; 
 scalar_t__ REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SM (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ath9k_hw_disable_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_enable_interrupts (struct ath_hw*) ; 

bool ath9k_hw_updatetxtriglevel(struct ath_hw *ah, bool bIncTrigLevel)
{
	u32 txcfg, curLevel, newLevel;

	if (ah->tx_trig_level >= ah->config.max_txtrig_level)
		return false;

	ath9k_hw_disable_interrupts(ah);

	txcfg = REG_READ(ah, AR_TXCFG);
	curLevel = MS(txcfg, AR_FTRIG);
	newLevel = curLevel;
	if (bIncTrigLevel) {
		if (curLevel < ah->config.max_txtrig_level)
			newLevel++;
	} else if (curLevel > MIN_TX_FIFO_THRESHOLD)
		newLevel--;
	if (newLevel != curLevel)
		REG_WRITE(ah, AR_TXCFG,
			  (txcfg & ~AR_FTRIG) | SM(newLevel, AR_FTRIG));

	ath9k_hw_enable_interrupts(ah);

	ah->tx_trig_level = newLevel;

	return newLevel != curLevel;
}