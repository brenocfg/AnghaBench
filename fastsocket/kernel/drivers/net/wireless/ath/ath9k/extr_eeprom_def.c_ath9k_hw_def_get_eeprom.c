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
struct modal_eep_header {int* noiseFloorThreshCh; int ob; int db; int* antennaGainCh; } ;
struct base_eep_header {int* regDmn; int deviceCap; int opCapFlags; int rfSilent; int txMask; int rxMask; int fastClk5g; int rxGainType; int txGainType; int rcChainMask; int dacHiPwrMode_5G; int frac_n_5g; int pwr_table_offset; int /*<<< orphan*/  openLoopPwrCntl; int /*<<< orphan*/  macAddr; } ;
struct ar5416_eeprom_def {struct base_eep_header baseEepHeader; struct modal_eep_header* modalHeader; } ;
struct TYPE_2__ {struct ar5416_eeprom_def def; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
typedef  enum eeprom_param { ____Placeholder_eeprom_param } eeprom_param ;

/* Variables and functions */
 int AR5416_EEP_MINOR_VER_19 ; 
 int AR5416_EEP_MINOR_VER_20 ; 
 int AR5416_EEP_MINOR_VER_21 ; 
 int AR5416_EEP_MINOR_VER_22 ; 
 int AR5416_PWR_TABLE_OFFSET_DB ; 
 int AR5416_VER_MASK ; 
#define  EEP_ANTENNA_GAIN_2G 153 
#define  EEP_ANTENNA_GAIN_5G 152 
#define  EEP_DAC_HPWR_5G 151 
#define  EEP_DB_2 150 
#define  EEP_DB_5 149 
#define  EEP_FRAC_N_5G 148 
#define  EEP_FSTCLK_5G 147 
#define  EEP_MAC_LSW 146 
#define  EEP_MAC_MID 145 
#define  EEP_MAC_MSW 144 
#define  EEP_MINOR_REV 143 
#define  EEP_NFTHRESH_2 142 
#define  EEP_NFTHRESH_5 141 
#define  EEP_OB_2 140 
#define  EEP_OB_5 139 
#define  EEP_OL_PWRCTRL 138 
#define  EEP_OP_CAP 137 
#define  EEP_OP_MODE 136 
#define  EEP_PWR_TABLE_OFFSET 135 
#define  EEP_RC_CHAIN_MASK 134 
#define  EEP_REG_0 133 
#define  EEP_RF_SILENT 132 
#define  EEP_RXGAIN_TYPE 131 
#define  EEP_RX_MASK 130 
#define  EEP_TXGAIN_TYPE 129 
#define  EEP_TX_MASK 128 
 int get_unaligned_be16 (int /*<<< orphan*/ ) ; 
 int max_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static u32 ath9k_hw_def_get_eeprom(struct ath_hw *ah,
				   enum eeprom_param param)
{
	struct ar5416_eeprom_def *eep = &ah->eeprom.def;
	struct modal_eep_header *pModal = eep->modalHeader;
	struct base_eep_header *pBase = &eep->baseEepHeader;
	int band = 0;

	switch (param) {
	case EEP_NFTHRESH_5:
		return pModal[0].noiseFloorThreshCh[0];
	case EEP_NFTHRESH_2:
		return pModal[1].noiseFloorThreshCh[0];
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
	case EEP_OB_5:
		return pModal[0].ob;
	case EEP_DB_5:
		return pModal[0].db;
	case EEP_OB_2:
		return pModal[1].ob;
	case EEP_DB_2:
		return pModal[1].db;
	case EEP_MINOR_REV:
		return AR5416_VER_MASK;
	case EEP_TX_MASK:
		return pBase->txMask;
	case EEP_RX_MASK:
		return pBase->rxMask;
	case EEP_FSTCLK_5G:
		return pBase->fastClk5g;
	case EEP_RXGAIN_TYPE:
		return pBase->rxGainType;
	case EEP_TXGAIN_TYPE:
		return pBase->txGainType;
	case EEP_OL_PWRCTRL:
		if (AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_19)
			return pBase->openLoopPwrCntl ? true : false;
		else
			return false;
	case EEP_RC_CHAIN_MASK:
		if (AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_19)
			return pBase->rcChainMask;
		else
			return 0;
	case EEP_DAC_HPWR_5G:
		if (AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_20)
			return pBase->dacHiPwrMode_5G;
		else
			return 0;
	case EEP_FRAC_N_5G:
		if (AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_22)
			return pBase->frac_n_5g;
		else
			return 0;
	case EEP_PWR_TABLE_OFFSET:
		if (AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_21)
			return pBase->pwr_table_offset;
		else
			return AR5416_PWR_TABLE_OFFSET_DB;
	case EEP_ANTENNA_GAIN_2G:
		band = 1;
		/* fall through */
	case EEP_ANTENNA_GAIN_5G:
		return max_t(u8, max_t(u8,
			pModal[band].antennaGainCh[0],
			pModal[band].antennaGainCh[1]),
			pModal[band].antennaGainCh[2]);
	default:
		return 0;
	}
}