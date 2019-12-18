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
struct ti_lynx {int i2c_driven_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SERIAL_EEPROM_CONTROL ; 
 int /*<<< orphan*/  reg_write (struct ti_lynx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bit_setsda(void *data, int state)
{
	if (state) {
		  ((struct ti_lynx *) data)->i2c_driven_state |= 0x00000010;
	} else {
		  ((struct ti_lynx *) data)->i2c_driven_state &= ~0x00000010;
	}
	reg_write((struct ti_lynx *) data, SERIAL_EEPROM_CONTROL, ((struct ti_lynx *) data)->i2c_driven_state);
}