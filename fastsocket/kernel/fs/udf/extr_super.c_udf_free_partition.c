#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct udf_meta_data {int /*<<< orphan*/ * s_bitmap_fe; int /*<<< orphan*/ * s_mirror_fe; int /*<<< orphan*/ * s_metadata_fe; } ;
struct TYPE_7__ {int /*<<< orphan*/ * s_spar_map; } ;
struct TYPE_8__ {struct udf_meta_data s_metadata; TYPE_3__ s_sparing; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_bitmap; int /*<<< orphan*/ * s_table; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_bitmap; int /*<<< orphan*/ * s_table; } ;
struct udf_part_map {int s_partition_flags; scalar_t__ s_partition_type; TYPE_4__ s_type_specific; TYPE_2__ s_fspace; TYPE_1__ s_uspace; } ;

/* Variables and functions */
 scalar_t__ UDF_METADATA_MAP25 ; 
 int UDF_PART_FLAG_FREED_BITMAP ; 
 int UDF_PART_FLAG_FREED_TABLE ; 
 int UDF_PART_FLAG_UNALLOC_BITMAP ; 
 int UDF_PART_FLAG_UNALLOC_TABLE ; 
 scalar_t__ UDF_SPARABLE_MAP15 ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_sb_free_bitmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udf_free_partition(struct udf_part_map *map)
{
	int i;
	struct udf_meta_data *mdata;

	if (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_TABLE)
		iput(map->s_uspace.s_table);
	if (map->s_partition_flags & UDF_PART_FLAG_FREED_TABLE)
		iput(map->s_fspace.s_table);
	if (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_BITMAP)
		udf_sb_free_bitmap(map->s_uspace.s_bitmap);
	if (map->s_partition_flags & UDF_PART_FLAG_FREED_BITMAP)
		udf_sb_free_bitmap(map->s_fspace.s_bitmap);
	if (map->s_partition_type == UDF_SPARABLE_MAP15)
		for (i = 0; i < 4; i++)
			brelse(map->s_type_specific.s_sparing.s_spar_map[i]);
	else if (map->s_partition_type == UDF_METADATA_MAP25) {
		mdata = &map->s_type_specific.s_metadata;
		iput(mdata->s_metadata_fe);
		mdata->s_metadata_fe = NULL;

		iput(mdata->s_mirror_fe);
		mdata->s_mirror_fe = NULL;

		iput(mdata->s_bitmap_fe);
		mdata->s_bitmap_fe = NULL;
	}
}