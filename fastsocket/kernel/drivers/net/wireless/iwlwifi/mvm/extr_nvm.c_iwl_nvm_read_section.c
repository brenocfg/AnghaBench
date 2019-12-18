#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int,int,int) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_mvm*,char*,int) ; 
 int IWL_NVM_DEFAULT_CHUNK_SIZE ; 
 int iwl_nvm_read_chunk (struct iwl_mvm*,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_nvm_read_section(struct iwl_mvm *mvm, u16 section,
				u8 *data)
{
	u16 length, offset = 0;
	int ret;

	/* Set nvm section read length */
	length = IWL_NVM_DEFAULT_CHUNK_SIZE;

	ret = length;

	/* Read the NVM until exhausted (reading less than requested) */
	while (ret == length) {
		ret = iwl_nvm_read_chunk(mvm, section, offset, length, data);
		if (ret < 0) {
			IWL_ERR(mvm,
				"Cannot read NVM from section %d offset %d, length %d\n",
				section, offset, length);
			return ret;
		}
		offset += ret;
	}

	IWL_INFO(mvm, "NVM section %d read completed\n", section);
	return offset;
}