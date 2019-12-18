#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint32_t ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct uni_table_desc {int num_entries; int entry_size; int findex; } ;
struct TYPE_4__ {scalar_t__ revision_id; } ;
struct netxen_adapter {TYPE_2__ ahw; scalar_t__ file_prd_off; TYPE_1__* fw; } ;
typedef  scalar_t__ __le32 ;
struct TYPE_3__ {scalar_t__* data; scalar_t__ size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NX_IS_REVISION_P2 (scalar_t__) ; 
 scalar_t__ NX_IS_REVISION_P3 (scalar_t__) ; 
 int NX_UNI_CHIP_REV_OFF ; 
 int /*<<< orphan*/  NX_UNI_DIR_SECT_PRODUCT_TBL ; 
 int NX_UNI_FLAGS_OFF ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int netxen_p3_has_mn (struct netxen_adapter*) ; 
 struct uni_table_desc* nx_get_table_desc (scalar_t__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netxen_nic_validate_product_offs(struct netxen_adapter *adapter)
{
	struct uni_table_desc *ptab_descr;
	const u8 *unirom = adapter->fw->data;
	int mn_present = (NX_IS_REVISION_P2(adapter->ahw.revision_id)) ?
			1 : netxen_p3_has_mn(adapter);
	__le32 entries;
	__le32 entry_size;
	u32 tab_size;
	u32 i;

	ptab_descr = nx_get_table_desc(unirom, NX_UNI_DIR_SECT_PRODUCT_TBL);
	if (ptab_descr == NULL)
		return -EINVAL;

	entries = cpu_to_le32(ptab_descr->num_entries);
	entry_size = cpu_to_le32(ptab_descr->entry_size);
	tab_size = cpu_to_le32(ptab_descr->findex) + (entries * entry_size);

	if (adapter->fw->size < tab_size)
		return -EINVAL;

nomn:
	for (i = 0; i < entries; i++) {

		__le32 flags, file_chiprev, offs;
		u8 chiprev = adapter->ahw.revision_id;
		uint32_t flagbit;

		offs = cpu_to_le32(ptab_descr->findex) +
				(i * cpu_to_le32(ptab_descr->entry_size));
		flags = cpu_to_le32(*((int *)&unirom[offs] + NX_UNI_FLAGS_OFF));
		file_chiprev = cpu_to_le32(*((int *)&unirom[offs] +
							NX_UNI_CHIP_REV_OFF));

		flagbit = mn_present ? 1 : 2;

		if ((chiprev == file_chiprev) &&
					((1ULL << flagbit) & flags)) {
			adapter->file_prd_off = offs;
			return 0;
		}
	}

	if (mn_present && NX_IS_REVISION_P3(adapter->ahw.revision_id)) {
		mn_present = 0;
		goto nomn;
	}

	return -EINVAL;
}