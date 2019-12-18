#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct udf_inode_info {scalar_t__ i_alloc_type; int i_lenAlloc; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_position {int offset; TYPE_1__* bh; int /*<<< orphan*/  block; } ;
struct allocExtDesc {int /*<<< orphan*/  lengthAllocDescs; } ;
typedef  int int8_t ;
struct TYPE_6__ {int s_udfrev; } ;
struct TYPE_5__ {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_LONG ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 int /*<<< orphan*/  UDF_FLAG_STRICT ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  UDF_QUERY_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* UDF_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (TYPE_1__*) ; 
 int /*<<< orphan*/  get_bh (TYPE_1__*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (struct kernel_lb_addr*,int,int) ; 
 int /*<<< orphan*/  udf_free_blocks (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int udf_next_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int*,int) ; 
 int /*<<< orphan*/  udf_update_tag (scalar_t__,int) ; 
 int /*<<< orphan*/  udf_write_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,int) ; 

int8_t udf_delete_aext(struct inode *inode, struct extent_position epos,
		       struct kernel_lb_addr eloc, uint32_t elen)
{
	struct extent_position oepos;
	int adsize;
	int8_t etype;
	struct allocExtDesc *aed;
	struct udf_inode_info *iinfo;

	if (epos.bh) {
		get_bh(epos.bh);
		get_bh(epos.bh);
	}

	iinfo = UDF_I(inode);
	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		adsize = 0;

	oepos = epos;
	if (udf_next_aext(inode, &epos, &eloc, &elen, 1) == -1)
		return -1;

	while ((etype = udf_next_aext(inode, &epos, &eloc, &elen, 1)) != -1) {
		udf_write_aext(inode, &oepos, &eloc, (etype << 30) | elen, 1);
		if (oepos.bh != epos.bh) {
			oepos.block = epos.block;
			brelse(oepos.bh);
			get_bh(epos.bh);
			oepos.bh = epos.bh;
			oepos.offset = epos.offset - adsize;
		}
	}
	memset(&eloc, 0x00, sizeof(struct kernel_lb_addr));
	elen = 0;

	if (epos.bh != oepos.bh) {
		udf_free_blocks(inode->i_sb, inode, &epos.block, 0, 1);
		udf_write_aext(inode, &oepos, &eloc, elen, 1);
		udf_write_aext(inode, &oepos, &eloc, elen, 1);
		if (!oepos.bh) {
			iinfo->i_lenAlloc -= (adsize * 2);
			mark_inode_dirty(inode);
		} else {
			aed = (struct allocExtDesc *)oepos.bh->b_data;
			le32_add_cpu(&aed->lengthAllocDescs, -(2 * adsize));
			if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
			    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
				udf_update_tag(oepos.bh->b_data,
						oepos.offset - (2 * adsize));
			else
				udf_update_tag(oepos.bh->b_data,
						sizeof(struct allocExtDesc));
			mark_buffer_dirty_inode(oepos.bh, inode);
		}
	} else {
		udf_write_aext(inode, &oepos, &eloc, elen, 1);
		if (!oepos.bh) {
			iinfo->i_lenAlloc -= adsize;
			mark_inode_dirty(inode);
		} else {
			aed = (struct allocExtDesc *)oepos.bh->b_data;
			le32_add_cpu(&aed->lengthAllocDescs, -adsize);
			if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
			    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
				udf_update_tag(oepos.bh->b_data,
						epos.offset - adsize);
			else
				udf_update_tag(oepos.bh->b_data,
						sizeof(struct allocExtDesc));
			mark_buffer_dirty_inode(oepos.bh, inode);
		}
	}

	brelse(epos.bh);
	brelse(oepos.bh);

	return (elen >> 30);
}