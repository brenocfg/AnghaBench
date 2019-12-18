#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int txrxgain; } ;
struct ar9300_eeprom {TYPE_2__ baseEepHeader; } ;
struct TYPE_3__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
typedef  int s32 ;

/* Variables and functions */

s32 ar9003_hw_get_rx_gain_idx(struct ath_hw *ah)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	return (eep->baseEepHeader.txrxgain) & 0xf; /* bits 3:0 */
}