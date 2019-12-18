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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 iwl_eeprom_query16(const u8 *eeprom, size_t eeprom_size, int offset)
{
	if (WARN_ON(offset + sizeof(u16) > eeprom_size))
		return 0;
	return le16_to_cpup((__le16 *)(eeprom + offset));
}