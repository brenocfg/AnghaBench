#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct modal_eep_header {int antCtrlCommon; int* antCtrlChain; scalar_t__* xpaBiasLvlFreq; scalar_t__ xpaBiasLvl; TYPE_6__* spurChans; } ;
struct TYPE_8__ {scalar_t__ devid; } ;
struct TYPE_11__ {scalar_t__ length; scalar_t__ checksum; scalar_t__ version; scalar_t__* regDmn; scalar_t__ rfSilent; scalar_t__ blueToothOptions; scalar_t__ deviceCap; scalar_t__ pwdclkind; } ;
struct ar5416_eeprom_def {struct modal_eep_header* modalHeader; TYPE_5__ baseEepHeader; } ;
struct TYPE_10__ {struct ar5416_eeprom_def def; } ;
struct ath_hw {int need_an_top2_fixup; TYPE_2__ hw_version; TYPE_1__* eep_ops; TYPE_4__ eeprom; } ;
struct ath_common {TYPE_3__* bus_ops; } ;
struct TYPE_12__ {scalar_t__ spurChan; } ;
struct TYPE_9__ {scalar_t__ ath_bus_type; } ;
struct TYPE_7__ {scalar_t__ (* get_eeprom_rev ) (struct ath_hw*) ;int /*<<< orphan*/  (* get_eeprom_ver ) (struct ath_hw*) ;} ;

/* Variables and functions */
 scalar_t__ AR5416_EEPROM_MAGIC ; 
 int /*<<< orphan*/  AR5416_EEPROM_MAGIC_OFFSET ; 
 scalar_t__ AR5416_EEP_NO_BACK_VER ; 
 int /*<<< orphan*/  AR5416_EEP_VER ; 
 int AR5416_MAX_CHAINS ; 
 scalar_t__ AR9280_DEVID_PCI ; 
 int ARRAY_SIZE (struct modal_eep_header*) ; 
 int AR_EEPROM_MODAL_SPURS ; 
 scalar_t__ AR_SREV_9280 (struct ath_hw*) ; 
 scalar_t__ ATH_USB ; 
 int /*<<< orphan*/  EEPROM ; 
 int EINVAL ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_nvram_read (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ath9k_hw_use_flash (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*) ; 
 scalar_t__ stub2 (struct ath_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ath_hw*) ; 
 scalar_t__ swab16 (scalar_t__) ; 
 int swab32 (int) ; 

__attribute__((used)) static int ath9k_hw_def_check_eeprom(struct ath_hw *ah)
{
	struct ar5416_eeprom_def *eep = &ah->eeprom.def;
	struct ath_common *common = ath9k_hw_common(ah);
	u16 *eepdata, temp, magic, magic2;
	u32 sum = 0, el;
	bool need_swap = false;
	int i, addr, size;

	if (!ath9k_hw_nvram_read(ah, AR5416_EEPROM_MAGIC_OFFSET, &magic)) {
		ath_err(common, "Reading Magic # failed\n");
		return false;
	}

	if (!ath9k_hw_use_flash(ah)) {
		ath_dbg(common, EEPROM, "Read Magic = 0x%04X\n", magic);

		if (magic != AR5416_EEPROM_MAGIC) {
			magic2 = swab16(magic);

			if (magic2 == AR5416_EEPROM_MAGIC) {
				size = sizeof(struct ar5416_eeprom_def);
				need_swap = true;
				eepdata = (u16 *) (&ah->eeprom);

				for (addr = 0; addr < size / sizeof(u16); addr++) {
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
		el = swab16(ah->eeprom.def.baseEepHeader.length);
	else
		el = ah->eeprom.def.baseEepHeader.length;

	if (el > sizeof(struct ar5416_eeprom_def))
		el = sizeof(struct ar5416_eeprom_def) / sizeof(u16);
	else
		el = el / sizeof(u16);

	eepdata = (u16 *)(&ah->eeprom);

	for (i = 0; i < el; i++)
		sum ^= *eepdata++;

	if (need_swap) {
		u32 integer, j;
		u16 word;

		ath_dbg(common, EEPROM,
			"EEPROM Endianness is not native.. Changing.\n");

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

		for (j = 0; j < ARRAY_SIZE(eep->modalHeader); j++) {
			struct modal_eep_header *pModal =
				&eep->modalHeader[j];
			integer = swab32(pModal->antCtrlCommon);
			pModal->antCtrlCommon = integer;

			for (i = 0; i < AR5416_MAX_CHAINS; i++) {
				integer = swab32(pModal->antCtrlChain[i]);
				pModal->antCtrlChain[i] = integer;
			}
			for (i = 0; i < 3; i++) {
				word = swab16(pModal->xpaBiasLvlFreq[i]);
				pModal->xpaBiasLvlFreq[i] = word;
			}

			for (i = 0; i < AR_EEPROM_MODAL_SPURS; i++) {
				word = swab16(pModal->spurChans[i].spurChan);
				pModal->spurChans[i].spurChan = word;
			}
		}
	}

	if (sum != 0xffff || ah->eep_ops->get_eeprom_ver(ah) != AR5416_EEP_VER ||
	    ah->eep_ops->get_eeprom_rev(ah) < AR5416_EEP_NO_BACK_VER) {
		ath_err(common, "Bad EEPROM checksum 0x%x or revision 0x%04x\n",
			sum, ah->eep_ops->get_eeprom_ver(ah));
		return -EINVAL;
	}

	/* Enable fixup for AR_AN_TOP2 if necessary */
	if ((ah->hw_version.devid == AR9280_DEVID_PCI) &&
	    ((eep->baseEepHeader.version & 0xff) > 0x0a) &&
	    (eep->baseEepHeader.pwdclkind == 0))
		ah->need_an_top2_fixup = true;

	if ((common->bus_ops->ath_bus_type == ATH_USB) &&
	    (AR_SREV_9280(ah)))
		eep->modalHeader[0].xpaBiasLvl = 0;

	return 0;
}