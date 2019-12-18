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
typedef  int /*<<< orphan*/  u32 ;
struct fw_card {int* topology_map; TYPE_1__* root_node; } ;
struct TYPE_2__ {int node_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_compute_block_crc (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void update_topology_map(struct fw_card *card,
				u32 *self_ids, int self_id_count)
{
	int node_count;

	card->topology_map[1]++;
	node_count = (card->root_node->node_id & 0x3f) + 1;
	card->topology_map[2] = (node_count << 16) | self_id_count;
	card->topology_map[0] = (self_id_count + 2) << 16;
	memcpy(&card->topology_map[3], self_ids, self_id_count * 4);
	fw_compute_block_crc(card->topology_map);
}