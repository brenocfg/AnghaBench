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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct ath_hw {scalar_t__ modes_index; int /*<<< orphan*/  iniAdditional; int /*<<< orphan*/  iniModesFastClock; int /*<<< orphan*/  iniModesTxGain; int /*<<< orphan*/  ini_radio_post_sys2ant; int /*<<< orphan*/ * iniRadio; int /*<<< orphan*/ * iniBB; int /*<<< orphan*/ * iniMac; int /*<<< orphan*/ * iniSOC; } ;
struct ath9k_channel {int chanmode; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9462_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 size_t ATH_INI_POST ; 
#define  CHANNEL_A 136 
#define  CHANNEL_A_HT20 135 
#define  CHANNEL_A_HT40MINUS 134 
#define  CHANNEL_A_HT40PLUS 133 
#define  CHANNEL_B 132 
#define  CHANNEL_G 131 
#define  CHANNEL_G_HT20 130 
#define  CHANNEL_G_HT40MINUS 129 
#define  CHANNEL_G_HT40PLUS 128 
 int EINVAL ; 
 scalar_t__ IS_CHAN_A_FAST_CLOCK (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  REG_WRITE_ARRAY (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  ar9003_hw_prog_ini (struct ath_hw*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ar9003_hw_set_rfmode (struct ath_hw*,struct ath9k_channel*) ; 

__attribute__((used)) static int ar9003_hw_fast_chan_change(struct ath_hw *ah,
				      struct ath9k_channel *chan,
				      u8 *ini_reloaded)
{
	unsigned int regWrites = 0;
	u32 modesIndex;

	switch (chan->chanmode) {
	case CHANNEL_A:
	case CHANNEL_A_HT20:
		modesIndex = 1;
		break;
	case CHANNEL_A_HT40PLUS:
	case CHANNEL_A_HT40MINUS:
		modesIndex = 2;
		break;
	case CHANNEL_G:
	case CHANNEL_G_HT20:
	case CHANNEL_B:
		modesIndex = 4;
		break;
	case CHANNEL_G_HT40PLUS:
	case CHANNEL_G_HT40MINUS:
		modesIndex = 3;
		break;

	default:
		return -EINVAL;
	}

	if (modesIndex == ah->modes_index) {
		*ini_reloaded = false;
		goto set_rfmode;
	}

	ar9003_hw_prog_ini(ah, &ah->iniSOC[ATH_INI_POST], modesIndex);
	ar9003_hw_prog_ini(ah, &ah->iniMac[ATH_INI_POST], modesIndex);
	ar9003_hw_prog_ini(ah, &ah->iniBB[ATH_INI_POST], modesIndex);
	ar9003_hw_prog_ini(ah, &ah->iniRadio[ATH_INI_POST], modesIndex);

	if (AR_SREV_9462_20(ah))
		ar9003_hw_prog_ini(ah, &ah->ini_radio_post_sys2ant,
				   modesIndex);

	REG_WRITE_ARRAY(&ah->iniModesTxGain, modesIndex, regWrites);

	/*
	 * For 5GHz channels requiring Fast Clock, apply
	 * different modal values.
	 */
	if (IS_CHAN_A_FAST_CLOCK(ah, chan))
		REG_WRITE_ARRAY(&ah->iniModesFastClock, modesIndex, regWrites);

	if (AR_SREV_9565(ah))
		REG_WRITE_ARRAY(&ah->iniModesFastClock, 1, regWrites);

	REG_WRITE_ARRAY(&ah->iniAdditional, 1, regWrites);

	ah->modes_index = modesIndex;
	*ini_reloaded = true;

set_rfmode:
	ar9003_hw_set_rfmode(ah, chan);
	return 0;
}