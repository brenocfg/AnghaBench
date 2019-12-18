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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iwl_eeprom_channel {int dummy; } ;
struct iwl_cfg {TYPE_1__* eeprom_params; } ;
struct TYPE_2__ {int* regulatory_bands; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int INDIRECT_ADDRESS ; 
 int INDIRECT_REGULATORY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * iwl_eeprom_band_1 ; 
 int /*<<< orphan*/ * iwl_eeprom_band_2 ; 
 int /*<<< orphan*/ * iwl_eeprom_band_3 ; 
 int /*<<< orphan*/ * iwl_eeprom_band_4 ; 
 int /*<<< orphan*/ * iwl_eeprom_band_5 ; 
 int /*<<< orphan*/ * iwl_eeprom_band_6 ; 
 int /*<<< orphan*/ * iwl_eeprom_band_7 ; 
 scalar_t__ iwl_eeprom_query_addr (int /*<<< orphan*/  const*,size_t,int) ; 

__attribute__((used)) static void iwl_init_band_reference(const struct iwl_cfg *cfg,
				    const u8 *eeprom, size_t eeprom_size,
				    int eeprom_band, int *eeprom_ch_count,
				    const struct iwl_eeprom_channel **ch_info,
				    const u8 **eeprom_ch_array)
{
	u32 offset = cfg->eeprom_params->regulatory_bands[eeprom_band - 1];

	offset |= INDIRECT_ADDRESS | INDIRECT_REGULATORY;

	*ch_info = (void *)iwl_eeprom_query_addr(eeprom, eeprom_size, offset);

	switch (eeprom_band) {
	case 1:		/* 2.4GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_1);
		*eeprom_ch_array = iwl_eeprom_band_1;
		break;
	case 2:		/* 4.9GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_2);
		*eeprom_ch_array = iwl_eeprom_band_2;
		break;
	case 3:		/* 5.2GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_3);
		*eeprom_ch_array = iwl_eeprom_band_3;
		break;
	case 4:		/* 5.5GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_4);
		*eeprom_ch_array = iwl_eeprom_band_4;
		break;
	case 5:		/* 5.7GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_5);
		*eeprom_ch_array = iwl_eeprom_band_5;
		break;
	case 6:		/* 2.4GHz ht40 channels */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_6);
		*eeprom_ch_array = iwl_eeprom_band_6;
		break;
	case 7:		/* 5 GHz ht40 channels */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_7);
		*eeprom_ch_array = iwl_eeprom_band_7;
		break;
	default:
		*eeprom_ch_count = 0;
		*eeprom_ch_array = NULL;
		WARN_ON(1);
	}
}