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
struct iwl_nvm_section {scalar_t__ data; } ;
struct iwl_nvm_data {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  cfg; TYPE_1__* trans; struct iwl_nvm_section* nvm_sections; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 size_t NVM_SECTION_TYPE_CALIBRATION ; 
 size_t NVM_SECTION_TYPE_HW ; 
 size_t NVM_SECTION_TYPE_SW ; 
 scalar_t__ WARN_ON (int) ; 
 struct iwl_nvm_data* iwl_parse_nvm_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct iwl_nvm_data *
iwl_parse_nvm_sections(struct iwl_mvm *mvm)
{
	struct iwl_nvm_section *sections = mvm->nvm_sections;
	const __le16 *hw, *sw, *calib;

	/* Checking for required sections */
	if (!mvm->nvm_sections[NVM_SECTION_TYPE_SW].data ||
	    !mvm->nvm_sections[NVM_SECTION_TYPE_HW].data) {
		IWL_ERR(mvm, "Can't parse empty NVM sections\n");
		return NULL;
	}

	if (WARN_ON(!mvm->cfg))
		return NULL;

	hw = (const __le16 *)sections[NVM_SECTION_TYPE_HW].data;
	sw = (const __le16 *)sections[NVM_SECTION_TYPE_SW].data;
	calib = (const __le16 *)sections[NVM_SECTION_TYPE_CALIBRATION].data;
	return iwl_parse_nvm_data(mvm->trans->dev, mvm->cfg, hw, sw, calib);
}