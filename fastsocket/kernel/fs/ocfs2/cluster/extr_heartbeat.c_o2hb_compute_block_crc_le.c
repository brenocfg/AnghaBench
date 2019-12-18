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
typedef  int /*<<< orphan*/  u32 ;
struct o2hb_region {int /*<<< orphan*/  hr_block_bytes; } ;
struct o2hb_disk_heartbeat_block {int /*<<< orphan*/  hb_cksum; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 o2hb_compute_block_crc_le(struct o2hb_region *reg,
				     struct o2hb_disk_heartbeat_block *hb_block)
{
	__le32 old_cksum;
	u32 ret;

	/* We want to compute the block crc with a 0 value in the
	 * hb_cksum field. Save it off here and replace after the
	 * crc. */
	old_cksum = hb_block->hb_cksum;
	hb_block->hb_cksum = 0;

	ret = crc32_le(0, (unsigned char *) hb_block, reg->hr_block_bytes);

	hb_block->hb_cksum = old_cksum;

	return ret;
}