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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct hfs_find_data {TYPE_2__* key; } ;
struct hfs_extent {int /*<<< orphan*/  count; } ;
struct hfs_cat_file {struct hfs_extent* RExtRec; int /*<<< orphan*/  RPyLen; struct hfs_extent* ExtRec; int /*<<< orphan*/  PyLen; int /*<<< orphan*/  FlNum; } ;
struct TYPE_6__ {int /*<<< orphan*/  ext_tree; scalar_t__ alloc_blksz; } ;
struct TYPE_4__ {int /*<<< orphan*/  FABN; } ;
struct TYPE_5__ {TYPE_1__ ext; } ;

/* Variables and functions */
 int HFS_FK_DATA ; 
 TYPE_3__* HFS_SB (struct super_block*) ; 
 int __hfs_ext_read_extent (struct hfs_find_data*,struct hfs_extent*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_brec_remove (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int hfs_free_extents (struct super_block*,struct hfs_extent*,scalar_t__,scalar_t__) ; 

int hfs_free_fork(struct super_block *sb, struct hfs_cat_file *file, int type)
{
	struct hfs_find_data fd;
	u32 total_blocks, blocks, start;
	u32 cnid = be32_to_cpu(file->FlNum);
	struct hfs_extent *extent;
	int res, i;

	if (type == HFS_FK_DATA) {
		total_blocks = be32_to_cpu(file->PyLen);
		extent = file->ExtRec;
	} else {
		total_blocks = be32_to_cpu(file->RPyLen);
		extent = file->RExtRec;
	}
	total_blocks /= HFS_SB(sb)->alloc_blksz;
	if (!total_blocks)
		return 0;

	blocks = 0;
	for (i = 0; i < 3; extent++, i++)
		blocks += be16_to_cpu(extent[i].count);

	res = hfs_free_extents(sb, extent, blocks, blocks);
	if (res)
		return res;
	if (total_blocks == blocks)
		return 0;

	hfs_find_init(HFS_SB(sb)->ext_tree, &fd);
	do {
		res = __hfs_ext_read_extent(&fd, extent, cnid, total_blocks, type);
		if (res)
			break;
		start = be16_to_cpu(fd.key->ext.FABN);
		hfs_free_extents(sb, extent, total_blocks - start, total_blocks);
		hfs_brec_remove(&fd);
		total_blocks = start;
	} while (total_blocks > blocks);
	hfs_find_exit(&fd);

	return res;
}