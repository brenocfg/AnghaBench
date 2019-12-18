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
struct ti_lynx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SERIAL_EEPROM_CONTROL ; 
 int reg_read (struct ti_lynx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bit_getsda(void *data)
{
	return reg_read((struct ti_lynx *) data, SERIAL_EEPROM_CONTROL) & 0x00000010;
}