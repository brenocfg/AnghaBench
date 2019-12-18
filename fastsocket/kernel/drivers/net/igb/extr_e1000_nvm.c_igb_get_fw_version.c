#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* read ) (struct e1000_hw*,int,int,int*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int type; } ;
struct e1000_hw {TYPE_3__ nvm; TYPE_1__ mac; } ;
struct e1000_fw_version {int eep_major; int eep_minor; int eep_build; int or_valid; int or_major; int or_build; int or_patch; int etrack_id; } ;

/* Variables and functions */
 int NVM_COMB_VER_MASK ; 
 int NVM_COMB_VER_OFF ; 
 int NVM_COMB_VER_PTR ; 
 int NVM_COMB_VER_SHFT ; 
 int NVM_ETRACK_HIWORD ; 
 int NVM_ETRACK_SHIFT ; 
 int NVM_ETRACK_VALID ; 
 int NVM_ETRACK_WORD ; 
 int NVM_HEX_CONV ; 
 int NVM_HEX_TENS ; 
 int NVM_IMAGE_ID_MASK ; 
 int NVM_MAJOR_MASK ; 
 int NVM_MAJOR_SHIFT ; 
 int NVM_MINOR_MASK ; 
 int NVM_MINOR_SHIFT ; 
 int NVM_NEW_DEC_MASK ; 
 int NVM_VERSION ; 
 int NVM_VER_INVALID ; 
#define  e1000_82575 133 
#define  e1000_82576 132 
#define  e1000_82580 131 
#define  e1000_i210 130 
#define  e1000_i211 129 
#define  e1000_i350 128 
 int /*<<< orphan*/  igb_get_flash_presence_i210 (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_read_invm_version (struct e1000_hw*,struct e1000_fw_version*) ; 
 int /*<<< orphan*/  memset (struct e1000_fw_version*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub6 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub7 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub8 (struct e1000_hw*,int,int,int*) ; 

void igb_get_fw_version(struct e1000_hw *hw, struct e1000_fw_version *fw_vers)
{
	u16 eeprom_verh, eeprom_verl, etrack_test, fw_version;
	u8 q, hval, rem, result;
	u16 comb_verh, comb_verl, comb_offset;

	memset(fw_vers, 0, sizeof(struct e1000_fw_version));

	/* basic eeprom version numbers and bits used vary by part and by tool
	 * used to create the nvm images. Check which data format we have.
	 */
	hw->nvm.ops.read(hw, NVM_ETRACK_HIWORD, 1, &etrack_test);
	switch (hw->mac.type) {
	case e1000_i211:
		igb_read_invm_version(hw, fw_vers);
		return;
	case e1000_82575:
	case e1000_82576:
	case e1000_82580:
		/* Use this format, unless EETRACK ID exists,
		 * then use alternate format
		 */
		if ((etrack_test &  NVM_MAJOR_MASK) != NVM_ETRACK_VALID) {
			hw->nvm.ops.read(hw, NVM_VERSION, 1, &fw_version);
			fw_vers->eep_major = (fw_version & NVM_MAJOR_MASK)
					      >> NVM_MAJOR_SHIFT;
			fw_vers->eep_minor = (fw_version & NVM_MINOR_MASK)
					      >> NVM_MINOR_SHIFT;
			fw_vers->eep_build = (fw_version & NVM_IMAGE_ID_MASK);
			goto etrack_id;
		}
		break;
	case e1000_i210:
		if (!(igb_get_flash_presence_i210(hw))) {
			igb_read_invm_version(hw, fw_vers);
			return;
		}
		/* fall through */
	case e1000_i350:
		/* find combo image version */
		hw->nvm.ops.read(hw, NVM_COMB_VER_PTR, 1, &comb_offset);
		if ((comb_offset != 0x0) &&
		    (comb_offset != NVM_VER_INVALID)) {

			hw->nvm.ops.read(hw, (NVM_COMB_VER_OFF + comb_offset
					 + 1), 1, &comb_verh);
			hw->nvm.ops.read(hw, (NVM_COMB_VER_OFF + comb_offset),
					 1, &comb_verl);

			/* get Option Rom version if it exists and is valid */
			if ((comb_verh && comb_verl) &&
			    ((comb_verh != NVM_VER_INVALID) &&
			     (comb_verl != NVM_VER_INVALID))) {

				fw_vers->or_valid = true;
				fw_vers->or_major =
					comb_verl >> NVM_COMB_VER_SHFT;
				fw_vers->or_build =
					(comb_verl << NVM_COMB_VER_SHFT)
					| (comb_verh >> NVM_COMB_VER_SHFT);
				fw_vers->or_patch =
					comb_verh & NVM_COMB_VER_MASK;
			}
		}
		break;
	default:
		return;
	}
	hw->nvm.ops.read(hw, NVM_VERSION, 1, &fw_version);
	fw_vers->eep_major = (fw_version & NVM_MAJOR_MASK)
			      >> NVM_MAJOR_SHIFT;

	/* check for old style version format in newer images*/
	if ((fw_version & NVM_NEW_DEC_MASK) == 0x0) {
		eeprom_verl = (fw_version & NVM_COMB_VER_MASK);
	} else {
		eeprom_verl = (fw_version & NVM_MINOR_MASK)
				>> NVM_MINOR_SHIFT;
	}
	/* Convert minor value to hex before assigning to output struct
	 * Val to be converted will not be higher than 99, per tool output
	 */
	q = eeprom_verl / NVM_HEX_CONV;
	hval = q * NVM_HEX_TENS;
	rem = eeprom_verl % NVM_HEX_CONV;
	result = hval + rem;
	fw_vers->eep_minor = result;

etrack_id:
	if ((etrack_test &  NVM_MAJOR_MASK) == NVM_ETRACK_VALID) {
		hw->nvm.ops.read(hw, NVM_ETRACK_WORD, 1, &eeprom_verl);
		hw->nvm.ops.read(hw, (NVM_ETRACK_WORD + 1), 1, &eeprom_verh);
		fw_vers->etrack_id = (eeprom_verh << NVM_ETRACK_SHIFT)
			| eeprom_verl;
	}
	return;
}