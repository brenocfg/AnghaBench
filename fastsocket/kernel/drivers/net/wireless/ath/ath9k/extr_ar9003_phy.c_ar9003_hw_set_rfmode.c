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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_FRAME_CTL ; 
 int /*<<< orphan*/  AR_PHY_FRAME_CTL_CF_OVERLAP_WINDOW ; 
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int AR_PHY_MODE_DYNAMIC ; 
 int AR_PHY_MODE_DYN_CCK_DISABLE ; 
 int AR_PHY_MODE_HALF ; 
 int AR_PHY_MODE_OFDM ; 
 int AR_PHY_MODE_QUARTER ; 
 scalar_t__ IS_CHAN_A_FAST_CLOCK (struct ath_hw*,struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_B (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_G (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HALF_RATE (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar9003_hw_set_rfmode(struct ath_hw *ah,
				 struct ath9k_channel *chan)
{
	u32 rfMode = 0;

	if (chan == NULL)
		return;

	rfMode |= (IS_CHAN_B(chan) || IS_CHAN_G(chan))
		? AR_PHY_MODE_DYNAMIC : AR_PHY_MODE_OFDM;

	if (IS_CHAN_A_FAST_CLOCK(ah, chan))
		rfMode |= (AR_PHY_MODE_DYNAMIC | AR_PHY_MODE_DYN_CCK_DISABLE);
	if (IS_CHAN_QUARTER_RATE(chan))
		rfMode |= AR_PHY_MODE_QUARTER;
	if (IS_CHAN_HALF_RATE(chan))
		rfMode |= AR_PHY_MODE_HALF;

	if (rfMode & (AR_PHY_MODE_QUARTER | AR_PHY_MODE_HALF))
		REG_RMW_FIELD(ah, AR_PHY_FRAME_CTL,
			      AR_PHY_FRAME_CTL_CF_OVERLAP_WINDOW, 3);

	REG_WRITE(ah, AR_PHY_MODE, rfMode);
}