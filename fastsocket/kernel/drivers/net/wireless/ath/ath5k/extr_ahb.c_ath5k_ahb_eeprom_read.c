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
struct TYPE_2__ {struct ar231x_board_config* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct ath_common {struct ath5k_hw* priv; } ;
struct ath5k_hw {int /*<<< orphan*/  dev; } ;
struct ar231x_board_config {scalar_t__ config; scalar_t__ radio; } ;

/* Variables and functions */
 int BOARD_CONFIG_BUFSZ ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ath5k_ahb_eeprom_read(struct ath_common *common, u32 off, u16 *data)
{
	struct ath5k_hw *ah = common->priv;
	struct platform_device *pdev = to_platform_device(ah->dev);
	struct ar231x_board_config *bcfg = pdev->dev.platform_data;
	u16 *eeprom, *eeprom_end;



	bcfg = pdev->dev.platform_data;
	eeprom = (u16 *) bcfg->radio;
	eeprom_end = ((void *) bcfg->config) + BOARD_CONFIG_BUFSZ;

	eeprom += off;
	if (eeprom > eeprom_end)
		return false;

	*data = *eeprom;
	return true;
}