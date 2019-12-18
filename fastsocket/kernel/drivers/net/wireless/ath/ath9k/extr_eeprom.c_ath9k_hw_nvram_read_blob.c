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
typedef  int /*<<< orphan*/  u16 ;
struct ath_hw {TYPE_1__* eeprom_blob; } ;
struct TYPE_2__ {int size; scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static bool ath9k_hw_nvram_read_blob(struct ath_hw *ah, u32 off,
				     u16 *data)
{
	u16 *blob_data;

	if (off * sizeof(u16) > ah->eeprom_blob->size)
		return false;

	blob_data = (u16 *)ah->eeprom_blob->data;
	*data =  blob_data[off];
	return true;
}