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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath_hw {scalar_t__ eeprom_blob; } ;
struct ath_common {TYPE_1__* bus_ops; } ;
struct TYPE_2__ {int (* eeprom_read ) (struct ath_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_nvram_read_blob (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ath_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool ath9k_hw_nvram_read(struct ath_hw *ah, u32 off, u16 *data)
{
	struct ath_common *common = ath9k_hw_common(ah);
	bool ret;

	if (ah->eeprom_blob)
		ret = ath9k_hw_nvram_read_blob(ah, off, data);
	else
		ret = common->bus_ops->eeprom_read(common, off, data);

	if (!ret)
		ath_dbg(common, EEPROM,
			"unable to read eeprom region at offset %u\n", off);

	return ret;
}