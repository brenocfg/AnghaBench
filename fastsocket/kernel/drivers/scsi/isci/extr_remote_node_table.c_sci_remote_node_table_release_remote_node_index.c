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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sci_remote_node_table {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCU_SSP_REMOTE_NODE_COUNT ; 
 scalar_t__ SCU_STP_REMOTE_NODE_COUNT ; 
 int /*<<< orphan*/  sci_remote_node_table_release_single_remote_node (struct sci_remote_node_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_remote_node_table_release_triple_remote_node (struct sci_remote_node_table*,int /*<<< orphan*/ ) ; 

void sci_remote_node_table_release_remote_node_index(
	struct sci_remote_node_table *remote_node_table,
	u32 remote_node_count,
	u16 remote_node_index)
{
	if (remote_node_count == SCU_SSP_REMOTE_NODE_COUNT) {
		sci_remote_node_table_release_single_remote_node(
			remote_node_table, remote_node_index);
	} else if (remote_node_count == SCU_STP_REMOTE_NODE_COUNT) {
		sci_remote_node_table_release_triple_remote_node(
			remote_node_table, remote_node_index);
	}
}