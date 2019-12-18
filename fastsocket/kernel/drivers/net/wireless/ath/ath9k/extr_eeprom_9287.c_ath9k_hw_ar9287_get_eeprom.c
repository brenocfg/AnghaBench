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
typedef  int u16 ;
struct modal_eep_ar9287_header {int* noiseFloorThreshCh; int /*<<< orphan*/ * antennaGainCh; } ;
struct base_eep_ar9287_header {int version; int* regDmn; int deviceCap; int opCapFlags; int rfSilent; int txMask; int rxMask; int deviceType; int openLoopPwrCntl; int tempSensSlope; int tempSensSlopePalOn; int /*<<< orphan*/  macAddr; } ;
struct ar9287_eeprom {struct base_eep_ar9287_header baseEepHeader; struct modal_eep_ar9287_header modalHeader; } ;
struct TYPE_2__ {struct ar9287_eeprom map9287; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
typedef  enum eeprom_param { ____Placeholder_eeprom_param } eeprom_param ;

/* Variables and functions */
 int AR9287_EEP_MINOR_VER_2 ; 
 int AR9287_EEP_MINOR_VER_3 ; 
 int AR9287_EEP_VER_MINOR_MASK ; 
#define  EEP_ANTENNA_GAIN_2G 143 
#define  EEP_DEV_TYPE 142 
#define  EEP_MAC_LSW 141 
#define  EEP_MAC_MID 140 
#define  EEP_MAC_MSW 139 
#define  EEP_MINOR_REV 138 
#define  EEP_NFTHRESH_2 137 
#define  EEP_OL_PWRCTRL 136 
#define  EEP_OP_CAP 135 
#define  EEP_OP_MODE 134 
#define  EEP_REG_0 133 
#define  EEP_RF_SILENT 132 
#define  EEP_RX_MASK 131 
#define  EEP_TEMPSENSE_SLOPE 130 
#define  EEP_TEMPSENSE_SLOPE_PAL_ON 129 
#define  EEP_TX_MASK 128 
 int get_unaligned_be16 (int /*<<< orphan*/ ) ; 
 int max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static u32 ath9k_hw_ar9287_get_eeprom(struct ath_hw *ah,
				      enum eeprom_param param)
{
	struct ar9287_eeprom *eep = &ah->eeprom.map9287;
	struct modal_eep_ar9287_header *pModal = &eep->modalHeader;
	struct base_eep_ar9287_header *pBase = &eep->baseEepHeader;
	u16 ver_minor;

	ver_minor = pBase->version & AR9287_EEP_VER_MINOR_MASK;

	switch (param) {
	case EEP_NFTHRESH_2:
		return pModal->noiseFloorThreshCh[0];
	case EEP_MAC_LSW:
		return get_unaligned_be16(pBase->macAddr);
	case EEP_MAC_MID:
		return get_unaligned_be16(pBase->macAddr + 2);
	case EEP_MAC_MSW:
		return get_unaligned_be16(pBase->macAddr + 4);
	case EEP_REG_0:
		return pBase->regDmn[0];
	case EEP_OP_CAP:
		return pBase->deviceCap;
	case EEP_OP_MODE:
		return pBase->opCapFlags;
	case EEP_RF_SILENT:
		return pBase->rfSilent;
	case EEP_MINOR_REV:
		return ver_minor;
	case EEP_TX_MASK:
		return pBase->txMask;
	case EEP_RX_MASK:
		return pBase->rxMask;
	case EEP_DEV_TYPE:
		return pBase->deviceType;
	case EEP_OL_PWRCTRL:
		return pBase->openLoopPwrCntl;
	case EEP_TEMPSENSE_SLOPE:
		if (ver_minor >= AR9287_EEP_MINOR_VER_2)
			return pBase->tempSensSlope;
		else
			return 0;
	case EEP_TEMPSENSE_SLOPE_PAL_ON:
		if (ver_minor >= AR9287_EEP_MINOR_VER_3)
			return pBase->tempSensSlopePalOn;
		else
			return 0;
	case EEP_ANTENNA_GAIN_2G:
		return max_t(u8, pModal->antennaGainCh[0],
				 pModal->antennaGainCh[1]);
	default:
		return 0;
	}
}