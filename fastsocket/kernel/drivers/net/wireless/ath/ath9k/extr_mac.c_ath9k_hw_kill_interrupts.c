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
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_IER ; 
 int /*<<< orphan*/  AR_IER_DISABLE ; 
 int /*<<< orphan*/  AR_INTR_ASYNC_ENABLE ; 
 int /*<<< orphan*/  AR_INTR_SYNC_ENABLE ; 
 int /*<<< orphan*/  AR_SREV_9100 (struct ath_hw*) ; 
 int /*<<< orphan*/  INTERRUPT ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

void ath9k_hw_kill_interrupts(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, INTERRUPT, "disable IER\n");
	REG_WRITE(ah, AR_IER, AR_IER_DISABLE);
	(void) REG_READ(ah, AR_IER);
	if (!AR_SREV_9100(ah)) {
		REG_WRITE(ah, AR_INTR_ASYNC_ENABLE, 0);
		(void) REG_READ(ah, AR_INTR_ASYNC_ENABLE);

		REG_WRITE(ah, AR_INTR_SYNC_ENABLE, 0);
		(void) REG_READ(ah, AR_INTR_SYNC_ENABLE);
	}
}