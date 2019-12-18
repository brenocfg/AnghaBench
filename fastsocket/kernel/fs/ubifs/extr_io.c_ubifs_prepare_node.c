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
struct ubifs_info {int min_io_size; } ;
struct ubifs_ch {void* crc; scalar_t__* padding; int /*<<< orphan*/  sqnum; int /*<<< orphan*/  group_type; void* len; void* magic; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int UBIFS_CH_SZ ; 
 int /*<<< orphan*/  UBIFS_CRC32_INIT ; 
 int UBIFS_NODE_MAGIC ; 
 int /*<<< orphan*/  UBIFS_NO_NODE_GROUP ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (unsigned long long) ; 
 int crc32 (int /*<<< orphan*/ ,void*,int) ; 
 unsigned long long next_sqnum (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_pad (struct ubifs_info*,void*,int) ; 

void ubifs_prepare_node(struct ubifs_info *c, void *node, int len, int pad)
{
	uint32_t crc;
	struct ubifs_ch *ch = node;
	unsigned long long sqnum = next_sqnum(c);

	ubifs_assert(len >= UBIFS_CH_SZ);

	ch->magic = cpu_to_le32(UBIFS_NODE_MAGIC);
	ch->len = cpu_to_le32(len);
	ch->group_type = UBIFS_NO_NODE_GROUP;
	ch->sqnum = cpu_to_le64(sqnum);
	ch->padding[0] = ch->padding[1] = 0;
	crc = crc32(UBIFS_CRC32_INIT, node + 8, len - 8);
	ch->crc = cpu_to_le32(crc);

	if (pad) {
		len = ALIGN(len, 8);
		pad = ALIGN(len, c->min_io_size) - len;
		ubifs_pad(c, node + len, pad);
	}
}