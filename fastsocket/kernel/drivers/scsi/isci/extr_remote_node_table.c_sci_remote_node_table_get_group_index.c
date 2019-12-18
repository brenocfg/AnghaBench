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
typedef  size_t u32 ;
struct sci_remote_node_table {size_t** remote_node_groups; size_t group_array_size; } ;

/* Variables and functions */
 size_t SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX ; 

__attribute__((used)) static u32 sci_remote_node_table_get_group_index(
	struct sci_remote_node_table *remote_node_table,
	u32 group_table_index)
{
	u32 dword_index;
	u32 *group_table;
	u32 bit_index;

	group_table = remote_node_table->remote_node_groups[group_table_index];

	for (dword_index = 0; dword_index < remote_node_table->group_array_size; dword_index++) {
		if (group_table[dword_index] != 0) {
			for (bit_index = 0; bit_index < 32; bit_index++) {
				if ((group_table[dword_index] & (1 << bit_index)) != 0) {
					return (dword_index * 32) + bit_index;
				}
			}
		}
	}

	return SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX;
}