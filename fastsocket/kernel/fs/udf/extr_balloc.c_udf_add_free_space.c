#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct udf_sb_info {TYPE_1__* s_lvid_bh; } ;
struct super_block {int dummy; } ;
struct logicalVolIntegrityDesc {int /*<<< orphan*/ * freeSpaceTable; } ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_updated_lvid (struct super_block*) ; 

__attribute__((used)) static void udf_add_free_space(struct super_block *sb, u16 partition, u32 cnt)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct logicalVolIntegrityDesc *lvid;

	if (!sbi->s_lvid_bh)
		return;

	lvid = (struct logicalVolIntegrityDesc *)sbi->s_lvid_bh->b_data;
	le32_add_cpu(&lvid->freeSpaceTable[partition], cnt);
	udf_updated_lvid(sb);
}