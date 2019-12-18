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
typedef  scalar_t__ u16 ;
struct super_block {int dummy; } ;
struct hfs_extent {scalar_t__ count; scalar_t__ block; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  hfs_clear_vbm_bits (struct super_block*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hfs_dump_extent (struct hfs_extent*) ; 

__attribute__((used)) static int hfs_free_extents(struct super_block *sb, struct hfs_extent *extent,
			    u16 offset, u16 block_nr)
{
	u16 count, start;
	int i;

	hfs_dump_extent(extent);
	for (i = 0; i < 3; extent++, i++) {
		count = be16_to_cpu(extent->count);
		if (offset == count)
			goto found;
		else if (offset < count)
			break;
		offset -= count;
	}
	/* panic? */
	return -EIO;
found:
	for (;;) {
		start = be16_to_cpu(extent->block);
		if (count <= block_nr) {
			hfs_clear_vbm_bits(sb, start, count);
			extent->block = 0;
			extent->count = 0;
			block_nr -= count;
		} else {
			count -= block_nr;
			hfs_clear_vbm_bits(sb, start + count, block_nr);
			extent->count = cpu_to_be16(count);
			block_nr = 0;
		}
		if (!block_nr || !i)
			return 0;
		i--;
		extent--;
		count = be16_to_cpu(extent->count);
	}
}