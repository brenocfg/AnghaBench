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
typedef  int uint32_t ;
struct ubifs_info {int dummy; } ;
struct ubifs_ch {void* crc; scalar_t__* padding; int /*<<< orphan*/  sqnum; int /*<<< orphan*/  group_type; void* len; void* magic; } ;

/* Variables and functions */
 int UBIFS_CH_SZ ; 
 int /*<<< orphan*/  UBIFS_CRC32_INIT ; 
 int /*<<< orphan*/  UBIFS_IN_NODE_GROUP ; 
 int /*<<< orphan*/  UBIFS_LAST_OF_NODE_GROUP ; 
 int UBIFS_NODE_MAGIC ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (unsigned long long) ; 
 int crc32 (int /*<<< orphan*/ ,void*,int) ; 
 unsigned long long next_sqnum (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 

void ubifs_prep_grp_node(struct ubifs_info *c, void *node, int len, int last)
{
	uint32_t crc;
	struct ubifs_ch *ch = node;
	unsigned long long sqnum = next_sqnum(c);

	ubifs_assert(len >= UBIFS_CH_SZ);

	ch->magic = cpu_to_le32(UBIFS_NODE_MAGIC);
	ch->len = cpu_to_le32(len);
	if (last)
		ch->group_type = UBIFS_LAST_OF_NODE_GROUP;
	else
		ch->group_type = UBIFS_IN_NODE_GROUP;
	ch->sqnum = cpu_to_le64(sqnum);
	ch->padding[0] = ch->padding[1] = 0;
	crc = crc32(UBIFS_CRC32_INIT, node + 8, len - 8);
	ch->crc = cpu_to_le32(crc);
}