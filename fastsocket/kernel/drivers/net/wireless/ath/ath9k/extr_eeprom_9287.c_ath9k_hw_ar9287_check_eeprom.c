#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_9__ {int antCtrlCommon; int* antCtrlChain; TYPE_3__* spurChans; } ;
struct TYPE_7__ {scalar_t__ length; scalar_t__ checksum; scalar_t__ version; scalar_t__* regDmn; scalar_t__ rfSilent; scalar_t__ blueToothOptions; scalar_t__ deviceCap; } ;
struct ar9287_eeprom {TYPE_4__ modalHeader; TYPE_2__ baseEepHeader; } ;
struct TYPE_6__ {struct ar9287_eeprom map9287; } ;
struct ath_hw {TYPE_5__* eep_ops; TYPE_1__ eeprom; } ;
struct ath_common {int dummy; } ;
struct TYPE_10__ {scalar_t__ (* get_eeprom_rev ) (struct ath_hw*) ;int /*<<< orphan*/  (* get_eeprom_ver ) (struct ath_hw*) ;} ;
struct TYPE_8__ {scalar_t__ spurChan; } ;

/* Variables and functions */
 scalar_t__ AR5416_EEPROM_MAGIC ; 
 int /*<<< orphan*/  AR5416_EEPROM_MAGIC_OFFSET ; 
 scalar_t__ AR5416_EEP_NO_BACK_VER ; 
 int /*<<< orphan*/  AR9287_EEP_VER ; 
 int AR9287_MAX_CHAINS ; 
 int AR_EEPROM_MODAL_SPURS ; 
 int /*<<< orphan*/  EEPROM ; 
 int EINVAL ; 
 int SIZE_EEPROM_AR9287 ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_nvram_read (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ath9k_hw_use_flash (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*) ; 
 scalar_t__ stub2 (struct ath_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ath_hw*) ; 
 scalar_t__ swab16 (scalar_t__) ; 
 int swab32 (int) ; 

__attribute__((used)) static int ath9k_hw_ar9287_check_eeprom(struct ath_hw *ah)
{
	u32 sum = 0, el, integer;
	u16 temp, word, magic, magic2, *eepdata;
	int i, addr;
	bool need_swap = false;
	struct ar9287_eeprom *eep = &ah->eeprom.map9287;
	struct ath_common *common = ath9k_hw_common(ah);

	if (!ath9k_hw_use_flash(ah)) {
		if (!ath9k_hw_nvram_read(ah, AR5416_EEPROM_MAGIC_OFFSET,
					 &magic)) {
			ath_err(common, "Reading Magic # failed\n");
			return false;
		}

		ath_dbg(common, EEPROM, "Read Magic = 0x%04X\n", magic);

		if (magic != AR5416_EEPROM_MAGIC) {
			magic2 = swab16(magic);

			if (magic2 == AR5416_EEPROM_MAGIC) {
				need_swap = true;
				eepdata = (u16 *)(&ah->eeprom);

				for (addr = 0; addr < SIZE_EEPROM_AR9287; addr++) {
					temp = swab16(*eepdata);
					*eepdata = temp;
					eepdata++;
				}
			} else {
				ath_err(common,
					"Invalid EEPROM Magic. Endianness mismatch.\n");
				return -EINVAL;
			}
		}
	}

	ath_dbg(common, EEPROM, "need_swap = %s\n",
		need_swap ? "True" : "False");

	if (need_swap)
		el = swab16(ah->eeprom.map9287.baseEepHeader.length);
	else
		el = ah->eeprom.map9287.baseEepHeader.length;

	if (el > sizeof(struct ar9287_eeprom))
		el = sizeof(struct ar9287_eeprom) / sizeof(u16);
	else
		el = el / sizeof(u16);

	eepdata = (u16 *)(&ah->eeprom);

	for (i = 0; i < el; i++)
		sum ^= *eepdata++;

	if (need_swap) {
		word = swab16(eep->baseEepHeader.length);
		eep->baseEepHeader.length = word;

		word = swab16(eep->baseEepHeader.checksum);
		eep->baseEepHeader.checksum = word;

		word = swab16(eep->baseEepHeader.version);
		eep->baseEepHeader.version = word;

		word = swab16(eep->baseEepHeader.regDmn[0]);
		eep->baseEepHeader.regDmn[0] = word;

		word = swab16(eep->baseEepHeader.regDmn[1]);
		eep->baseEepHeader.regDmn[1] = word;

		word = swab16(eep->baseEepHeader.rfSilent);
		eep->baseEepHeader.rfSilent = word;

		word = swab16(eep->baseEepHeader.blueToothOptions);
		eep->baseEepHeader.blueToothOptions = word;

		word = swab16(eep->baseEepHeader.deviceCap);
		eep->baseEepHeader.deviceCap = word;

		integer = swab32(eep->modalHeader.antCtrlCommon);
		eep->modalHeader.antCtrlCommon = integer;

		for (i = 0; i < AR9287_MAX_CHAINS; i++) {
			integer = swab32(eep->modalHeader.antCtrlChain[i]);
			eep->modalHeader.antCtrlChain[i] = integer;
		}

		for (i = 0; i < AR_EEPROM_MODAL_SPURS; i++) {
			word = swab16(eep->modalHeader.spurChans[i].spurChan);
			eep->modalHeader.spurChans[i].spurChan = word;
		}
	}

	if (sum != 0xffff || ah->eep_ops->get_eeprom_ver(ah) != AR9287_EEP_VER
	    || ah->eep_ops->get_eeprom_rev(ah) < AR5416_EEP_NO_BACK_VER) {
		ath_err(common, "Bad EEPROM checksum 0x%x or revision 0x%04x\n",
			sum, ah->eep_ops->get_eeprom_ver(ah));
		return -EINVAL;
	}

	return 0;
}