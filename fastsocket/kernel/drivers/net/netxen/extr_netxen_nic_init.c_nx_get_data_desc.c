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
struct uni_table_desc {int findex; int entry_size; } ;
struct uni_data_desc {int dummy; } ;
struct netxen_adapter {size_t file_prd_off; TYPE_1__* fw; } ;
typedef  size_t __le32 ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int cpu_to_le32 (int) ; 
 struct uni_table_desc* nx_get_table_desc (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static struct uni_data_desc *nx_get_data_desc(struct netxen_adapter *adapter,
			u32 section, u32 idx_offset)
{
	const u8 *unirom = adapter->fw->data;
	int idx = cpu_to_le32(*((int *)&unirom[adapter->file_prd_off] +
								idx_offset));
	struct uni_table_desc *tab_desc;
	__le32 offs;

	tab_desc = nx_get_table_desc(unirom, section);

	if (tab_desc == NULL)
		return NULL;

	offs = cpu_to_le32(tab_desc->findex) +
			(cpu_to_le32(tab_desc->entry_size) * idx);

	return (struct uni_data_desc *)&unirom[offs];
}