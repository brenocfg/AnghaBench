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
struct super_block {int dummy; } ;
struct hfsplus_extent {scalar_t__ block_count; scalar_t__ start_block; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ be32_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  hfsplus_block_free (struct super_block*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hfsplus_dump_extent (struct hfsplus_extent*) ; 

__attribute__((used)) static int hfsplus_free_extents(struct super_block *sb,
				struct hfsplus_extent *extent,
				u32 offset, u32 block_nr)
{
	u32 count, start;
	int i;

	hfsplus_dump_extent(extent);
	for (i = 0; i < 8; extent++, i++) {
		count = be32_to_cpu(extent->block_count);
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
		start = be32_to_cpu(extent->start_block);
		if (count <= block_nr) {
			hfsplus_block_free(sb, start, count);
			extent->block_count = 0;
			extent->start_block = 0;
			block_nr -= count;
		} else {
			count -= block_nr;
			hfsplus_block_free(sb, start + count, block_nr);
			extent->block_count = cpu_to_be32(count);
			block_nr = 0;
		}
		if (!block_nr || !i)
			return 0;
		i--;
		extent--;
		count = be32_to_cpu(extent->block_count);
	}
}