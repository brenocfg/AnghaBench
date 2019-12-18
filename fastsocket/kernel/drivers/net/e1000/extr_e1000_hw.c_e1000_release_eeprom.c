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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  delay_usec; } ;
struct e1000_hw {scalar_t__ mac_type; TYPE_1__ eeprom; } ;

/* Variables and functions */
 int E1000_EECD_CS ; 
 int E1000_EECD_DI ; 
 int E1000_EECD_REQ ; 
 int E1000_EECD_SK ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  EECD ; 
 scalar_t__ e1000_82544 ; 
 scalar_t__ e1000_eeprom_microwire ; 
 scalar_t__ e1000_eeprom_spi ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_release_eeprom(struct e1000_hw *hw)
{
	u32 eecd;

	e_dbg("e1000_release_eeprom");

	eecd = er32(EECD);

	if (hw->eeprom.type == e1000_eeprom_spi) {
		eecd |= E1000_EECD_CS;	/* Pull CS high */
		eecd &= ~E1000_EECD_SK;	/* Lower SCK */

		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();

		udelay(hw->eeprom.delay_usec);
	} else if (hw->eeprom.type == e1000_eeprom_microwire) {
		/* cleanup eeprom */

		/* CS on Microwire is active-high */
		eecd &= ~(E1000_EECD_CS | E1000_EECD_DI);

		ew32(EECD, eecd);

		/* Rising edge of clock */
		eecd |= E1000_EECD_SK;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(hw->eeprom.delay_usec);

		/* Falling edge of clock */
		eecd &= ~E1000_EECD_SK;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(hw->eeprom.delay_usec);
	}

	/* Stop requesting EEPROM access */
	if (hw->mac_type > e1000_82544) {
		eecd &= ~E1000_EECD_REQ;
		ew32(EECD, eecd);
	}
}