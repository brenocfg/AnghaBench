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
typedef  int /*<<< orphan*/  uint32_t ;
struct kernel_lb_addr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_position {int /*<<< orphan*/  bh; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int EXT_RECORDED_ALLOCATED ; 
 int /*<<< orphan*/  UDF_FLAG_VARCONV ; 
 scalar_t__ UDF_QUERY_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int inode_bmap (struct inode*,int /*<<< orphan*/ ,struct extent_position*,struct kernel_lb_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 long udf_fixed_to_variable (int) ; 
 int udf_get_lb_pblock (int /*<<< orphan*/ ,struct kernel_lb_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

long udf_block_map(struct inode *inode, sector_t block)
{
	struct kernel_lb_addr eloc;
	uint32_t elen;
	sector_t offset;
	struct extent_position epos = {};
	int ret;

	lock_kernel();

	if (inode_bmap(inode, block, &epos, &eloc, &elen, &offset) ==
						(EXT_RECORDED_ALLOCATED >> 30))
		ret = udf_get_lb_pblock(inode->i_sb, &eloc, offset);
	else
		ret = 0;

	unlock_kernel();
	brelse(epos.bh);

	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_VARCONV))
		return udf_fixed_to_variable(ret);
	else
		return ret;
}