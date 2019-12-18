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

/* Variables and functions */
 int /*<<< orphan*/  AR_BTCOEX_CTRL ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9003_mci_disable_interrupt (struct ath_hw*) ; 

void ar9003_mci_cleanup(struct ath_hw *ah)
{
	/* Turn off MCI and Jupiter mode. */
	REG_WRITE(ah, AR_BTCOEX_CTRL, 0x00);
	ar9003_mci_disable_interrupt(ah);
}