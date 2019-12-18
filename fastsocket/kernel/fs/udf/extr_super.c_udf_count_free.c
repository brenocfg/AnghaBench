#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udf_sb_info {unsigned int s_partition; struct udf_part_map* s_partmaps; TYPE_1__* s_lvid_bh; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_table; int /*<<< orphan*/  s_bitmap; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_table; int /*<<< orphan*/  s_bitmap; } ;
struct udf_part_map {int s_partition_flags; TYPE_3__ s_fspace; TYPE_2__ s_uspace; } ;
struct super_block {int dummy; } ;
struct logicalVolIntegrityDesc {int /*<<< orphan*/ * freeSpaceTable; int /*<<< orphan*/  numOfPartitions; } ;
struct TYPE_4__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int UDF_PART_FLAG_FREED_BITMAP ; 
 int UDF_PART_FLAG_FREED_TABLE ; 
 int UDF_PART_FLAG_UNALLOC_BITMAP ; 
 int UDF_PART_FLAG_UNALLOC_TABLE ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ udf_count_free_bitmap (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ udf_count_free_table (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int udf_count_free(struct super_block *sb)
{
	unsigned int accum = 0;
	struct udf_sb_info *sbi;
	struct udf_part_map *map;

	sbi = UDF_SB(sb);
	if (sbi->s_lvid_bh) {
		struct logicalVolIntegrityDesc *lvid =
			(struct logicalVolIntegrityDesc *)
			sbi->s_lvid_bh->b_data;
		if (le32_to_cpu(lvid->numOfPartitions) > sbi->s_partition) {
			accum = le32_to_cpu(
					lvid->freeSpaceTable[sbi->s_partition]);
			if (accum == 0xFFFFFFFF)
				accum = 0;
		}
	}

	if (accum)
		return accum;

	map = &sbi->s_partmaps[sbi->s_partition];
	if (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_BITMAP) {
		accum += udf_count_free_bitmap(sb,
					       map->s_uspace.s_bitmap);
	}
	if (map->s_partition_flags & UDF_PART_FLAG_FREED_BITMAP) {
		accum += udf_count_free_bitmap(sb,
					       map->s_fspace.s_bitmap);
	}
	if (accum)
		return accum;

	if (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_TABLE) {
		accum += udf_count_free_table(sb,
					      map->s_uspace.s_table);
	}
	if (map->s_partition_flags & UDF_PART_FLAG_FREED_TABLE) {
		accum += udf_count_free_table(sb,
					      map->s_fspace.s_table);
	}

	return accum;
}