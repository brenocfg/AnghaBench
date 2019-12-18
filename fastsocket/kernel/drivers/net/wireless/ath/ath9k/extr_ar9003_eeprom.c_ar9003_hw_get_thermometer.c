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
struct ar9300_base_eep_hdr {int miscConfiguration; } ;
struct ar9300_eeprom {struct ar9300_base_eep_hdr baseEepHeader; } ;
struct TYPE_2__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;

/* Variables and functions */

__attribute__((used)) static int ar9003_hw_get_thermometer(struct ath_hw *ah)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	struct ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;
	int thermometer =  (pBase->miscConfiguration >> 1) & 0x3;

	return --thermometer;
}