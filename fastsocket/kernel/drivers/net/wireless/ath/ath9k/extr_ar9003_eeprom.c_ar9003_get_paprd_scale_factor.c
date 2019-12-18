#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  papdRateMaskHt40; int /*<<< orphan*/  papdRateMaskHt20; } ;
struct TYPE_5__ {int /*<<< orphan*/  papdRateMaskHt20; } ;
struct ar9300_eeprom {TYPE_3__ modalHeader5G; TYPE_2__ modalHeader2G; } ;
struct TYPE_4__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
struct ath9k_channel {int channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9300_PAPRD_SCALE_1 ; 
 int /*<<< orphan*/  AR9300_PAPRD_SCALE_2 ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 unsigned int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

unsigned int ar9003_get_paprd_scale_factor(struct ath_hw *ah,
					   struct ath9k_channel *chan)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	if (IS_CHAN_2GHZ(chan))
		return MS(le32_to_cpu(eep->modalHeader2G.papdRateMaskHt20),
			  AR9300_PAPRD_SCALE_1);
	else {
		if (chan->channel >= 5700)
		return MS(le32_to_cpu(eep->modalHeader5G.papdRateMaskHt20),
			  AR9300_PAPRD_SCALE_1);
		else if (chan->channel >= 5400)
			return MS(le32_to_cpu(eep->modalHeader5G.papdRateMaskHt40),
				   AR9300_PAPRD_SCALE_2);
		else
			return MS(le32_to_cpu(eep->modalHeader5G.papdRateMaskHt40),
				  AR9300_PAPRD_SCALE_1);
	}
}