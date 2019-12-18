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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ analog_shiftreg; } ;
struct ath_hw {TYPE_1__ config; } ;

/* Variables and functions */
 int REG_READ (struct ath_hw*,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void ath9k_hw_analog_shift_rmw(struct ath_hw *ah, u32 reg, u32 mask,
			       u32 shift, u32 val)
{
	u32 regVal;

	regVal = REG_READ(ah, reg) & ~mask;
	regVal |= (val << shift) & mask;

	REG_WRITE(ah, reg, regVal);

	if (ah->config.analog_shiftreg)
		udelay(100);
}