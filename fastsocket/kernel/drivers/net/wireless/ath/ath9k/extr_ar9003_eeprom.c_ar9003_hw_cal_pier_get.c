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
struct ar9300_eeprom {struct ar9300_cal_data_per_freq_op_loop** calPierData2G; int /*<<< orphan*/ * calFreqPier2G; struct ar9300_cal_data_per_freq_op_loop** calPierData5G; int /*<<< orphan*/ * calFreqPier5G; } ;
struct TYPE_2__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
struct ath_common {int dummy; } ;
struct ar9300_cal_data_per_freq_op_loop {int refPower; int tempMeas; int voltMeas; } ;

/* Variables and functions */
 int AR9300_MAX_CHAINS ; 
 int AR9300_NUM_2G_CAL_PIERS ; 
 int AR9300_NUM_5G_CAL_PIERS ; 
 int /*<<< orphan*/  EEPROM ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_fbin2freq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ar9003_hw_cal_pier_get(struct ath_hw *ah,
				  int mode,
				  int ipier,
				  int ichain,
				  int *pfrequency,
				  int *pcorrection,
				  int *ptemperature, int *pvoltage)
{
	u8 *pCalPier;
	struct ar9300_cal_data_per_freq_op_loop *pCalPierStruct;
	int is2GHz;
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	struct ath_common *common = ath9k_hw_common(ah);

	if (ichain >= AR9300_MAX_CHAINS) {
		ath_dbg(common, EEPROM,
			"Invalid chain index, must be less than %d\n",
			AR9300_MAX_CHAINS);
		return -1;
	}

	if (mode) {		/* 5GHz */
		if (ipier >= AR9300_NUM_5G_CAL_PIERS) {
			ath_dbg(common, EEPROM,
				"Invalid 5GHz cal pier index, must be less than %d\n",
				AR9300_NUM_5G_CAL_PIERS);
			return -1;
		}
		pCalPier = &(eep->calFreqPier5G[ipier]);
		pCalPierStruct = &(eep->calPierData5G[ichain][ipier]);
		is2GHz = 0;
	} else {
		if (ipier >= AR9300_NUM_2G_CAL_PIERS) {
			ath_dbg(common, EEPROM,
				"Invalid 2GHz cal pier index, must be less than %d\n",
				AR9300_NUM_2G_CAL_PIERS);
			return -1;
		}

		pCalPier = &(eep->calFreqPier2G[ipier]);
		pCalPierStruct = &(eep->calPierData2G[ichain][ipier]);
		is2GHz = 1;
	}

	*pfrequency = ath9k_hw_fbin2freq(*pCalPier, is2GHz);
	*pcorrection = pCalPierStruct->refPower;
	*ptemperature = pCalPierStruct->tempMeas;
	*pvoltage = pCalPierStruct->voltMeas;

	return 0;
}