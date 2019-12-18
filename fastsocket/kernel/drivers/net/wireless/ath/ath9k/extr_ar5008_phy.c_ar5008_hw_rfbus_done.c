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
typedef  int u32 ;
struct ath_hw {int /*<<< orphan*/  curchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RFBUS_REQ ; 
 int /*<<< orphan*/  AR_PHY_RX_DELAY ; 
 int AR_PHY_RX_DELAY_DELAY ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_synth_delay (struct ath_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar5008_hw_rfbus_done(struct ath_hw *ah)
{
	u32 synthDelay = REG_READ(ah, AR_PHY_RX_DELAY) & AR_PHY_RX_DELAY_DELAY;

	ath9k_hw_synth_delay(ah, ah->curchan, synthDelay);

	REG_WRITE(ah, AR_PHY_RFBUS_REQ, 0);
}