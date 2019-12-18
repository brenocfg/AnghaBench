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
struct udf_sb_info {int s_partitions; int /*<<< orphan*/ * s_partmaps; int /*<<< orphan*/  s_lvid_bh; int /*<<< orphan*/  s_nls_map; scalar_t__ s_vat_inode; } ;
struct super_block {int s_flags; int /*<<< orphan*/ * s_fs_info; } ;

/* Variables and functions */
 int MS_RDONLY ; 
 int /*<<< orphan*/  UDF_FLAG_NLS_MAP ; 
 scalar_t__ UDF_QUERY_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  udf_close_lvid (struct super_block*) ; 
 int /*<<< orphan*/  udf_free_partition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void udf_put_super(struct super_block *sb)
{
	int i;
	struct udf_sb_info *sbi;

	sbi = UDF_SB(sb);

	lock_kernel();

	if (sbi->s_vat_inode)
		iput(sbi->s_vat_inode);
	if (sbi->s_partitions)
		for (i = 0; i < sbi->s_partitions; i++)
			udf_free_partition(&sbi->s_partmaps[i]);
#ifdef CONFIG_UDF_NLS
	if (UDF_QUERY_FLAG(sb, UDF_FLAG_NLS_MAP))
		unload_nls(sbi->s_nls_map);
#endif
	if (!(sb->s_flags & MS_RDONLY))
		udf_close_lvid(sb);
	brelse(sbi->s_lvid_bh);
	kfree(sbi->s_partmaps);
	kfree(sb->s_fs_info);
	sb->s_fs_info = NULL;

	unlock_kernel();
}