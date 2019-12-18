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
struct udf_sb_info {scalar_t__ s_last_block; } ;
struct super_block {int dummy; } ;
struct kernel_lb_addr {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  UDF_CLEAR_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDF_FLAG_VARCONV ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  UDF_SET_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ udf_scan_anchors (struct super_block*,scalar_t__,struct kernel_lb_addr*) ; 
 scalar_t__ udf_variable_to_fixed (scalar_t__) ; 

__attribute__((used)) static int udf_find_anchor(struct super_block *sb,
			   struct kernel_lb_addr *fileset)
{
	sector_t lastblock;
	struct udf_sb_info *sbi = UDF_SB(sb);

	lastblock = udf_scan_anchors(sb, sbi->s_last_block, fileset);
	if (lastblock)
		goto out;

	/* No anchor found? Try VARCONV conversion of block numbers */
	UDF_SET_FLAG(sb, UDF_FLAG_VARCONV);
	/* Firstly, we try to not convert number of the last block */
	lastblock = udf_scan_anchors(sb,
				udf_variable_to_fixed(sbi->s_last_block),
				fileset);
	if (lastblock)
		goto out;

	/* Secondly, we try with converted number of the last block */
	lastblock = udf_scan_anchors(sb, sbi->s_last_block, fileset);
	if (!lastblock) {
		/* VARCONV didn't help. Clear it. */
		UDF_CLEAR_FLAG(sb, UDF_FLAG_VARCONV);
		return 0;
	}
out:
	sbi->s_last_block = lastblock;
	return 1;
}