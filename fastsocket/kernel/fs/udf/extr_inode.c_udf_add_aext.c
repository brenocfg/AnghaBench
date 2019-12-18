#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_data; } ;
struct udf_inode_info {char* i_lenEAttr; int i_alloc_type; int i_lenAlloc; TYPE_1__ i_ext; } ;
struct tag {int dummy; } ;
struct short_ad {void* extPosition; void* extLength; } ;
struct long_ad {char* impUse; int /*<<< orphan*/  extLocation; void* extLength; } ;
struct kernel_lb_addr {int logicalBlockNum; int /*<<< orphan*/  partitionReferenceNum; } ;
struct inode {TYPE_2__* i_sb; } ;
struct extent_position {int offset; struct buffer_head* bh; struct kernel_lb_addr block; } ;
struct buffer_head {char* b_data; } ;
struct allocExtDesc {void* lengthAllocDescs; void* previousAllocExtLocation; } ;
typedef  int int8_t ;
struct TYPE_10__ {int s_udfrev; } ;
struct TYPE_9__ {int s_blocksize; } ;

/* Variables and functions */
 int EXT_NEXT_EXTENT_ALLOCDECS ; 
#define  ICBTAG_FLAG_AD_LONG 129 
#define  ICBTAG_FLAG_AD_SHORT 128 
 int /*<<< orphan*/  TAG_IDENT_AED ; 
 int /*<<< orphan*/  UDF_FLAG_STRICT ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  UDF_QUERY_FLAG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* UDF_SB (TYPE_2__*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_lelb (struct kernel_lb_addr) ; 
 int /*<<< orphan*/  le32_add_cpu (void**,int) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  udf_file_entry_alloc_offset (struct inode*) ; 
 int /*<<< orphan*/  udf_get_lb_pblock (TYPE_2__*,struct kernel_lb_addr*,int /*<<< orphan*/ ) ; 
 int udf_new_block (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  udf_new_tag (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 struct buffer_head* udf_tgetblk (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_update_tag (char*,int) ; 
 int udf_write_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

int8_t udf_add_aext(struct inode *inode, struct extent_position *epos,
		    struct kernel_lb_addr *eloc, uint32_t elen, int inc)
{
	int adsize;
	struct short_ad *sad = NULL;
	struct long_ad *lad = NULL;
	struct allocExtDesc *aed;
	int8_t etype;
	uint8_t *ptr;
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (!epos->bh)
		ptr = iinfo->i_ext.i_data + epos->offset -
			udf_file_entry_alloc_offset(inode) +
			iinfo->i_lenEAttr;
	else
		ptr = epos->bh->b_data + epos->offset;

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		return -1;

	if (epos->offset + (2 * adsize) > inode->i_sb->s_blocksize) {
		char *sptr, *dptr;
		struct buffer_head *nbh;
		int err, loffset;
		struct kernel_lb_addr obloc = epos->block;

		epos->block.logicalBlockNum = udf_new_block(inode->i_sb, NULL,
						obloc.partitionReferenceNum,
						obloc.logicalBlockNum, &err);
		if (!epos->block.logicalBlockNum)
			return -1;
		nbh = udf_tgetblk(inode->i_sb, udf_get_lb_pblock(inode->i_sb,
								 &epos->block,
								 0));
		if (!nbh)
			return -1;
		lock_buffer(nbh);
		memset(nbh->b_data, 0x00, inode->i_sb->s_blocksize);
		set_buffer_uptodate(nbh);
		unlock_buffer(nbh);
		mark_buffer_dirty_inode(nbh, inode);

		aed = (struct allocExtDesc *)(nbh->b_data);
		if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT))
			aed->previousAllocExtLocation =
					cpu_to_le32(obloc.logicalBlockNum);
		if (epos->offset + adsize > inode->i_sb->s_blocksize) {
			loffset = epos->offset;
			aed->lengthAllocDescs = cpu_to_le32(adsize);
			sptr = ptr - adsize;
			dptr = nbh->b_data + sizeof(struct allocExtDesc);
			memcpy(dptr, sptr, adsize);
			epos->offset = sizeof(struct allocExtDesc) + adsize;
		} else {
			loffset = epos->offset + adsize;
			aed->lengthAllocDescs = cpu_to_le32(0);
			sptr = ptr;
			epos->offset = sizeof(struct allocExtDesc);

			if (epos->bh) {
				aed = (struct allocExtDesc *)epos->bh->b_data;
				le32_add_cpu(&aed->lengthAllocDescs, adsize);
			} else {
				iinfo->i_lenAlloc += adsize;
				mark_inode_dirty(inode);
			}
		}
		if (UDF_SB(inode->i_sb)->s_udfrev >= 0x0200)
			udf_new_tag(nbh->b_data, TAG_IDENT_AED, 3, 1,
				    epos->block.logicalBlockNum, sizeof(struct tag));
		else
			udf_new_tag(nbh->b_data, TAG_IDENT_AED, 2, 1,
				    epos->block.logicalBlockNum, sizeof(struct tag));
		switch (iinfo->i_alloc_type) {
		case ICBTAG_FLAG_AD_SHORT:
			sad = (struct short_ad *)sptr;
			sad->extLength = cpu_to_le32(EXT_NEXT_EXTENT_ALLOCDECS |
						     inode->i_sb->s_blocksize);
			sad->extPosition =
				cpu_to_le32(epos->block.logicalBlockNum);
			break;
		case ICBTAG_FLAG_AD_LONG:
			lad = (struct long_ad *)sptr;
			lad->extLength = cpu_to_le32(EXT_NEXT_EXTENT_ALLOCDECS |
						     inode->i_sb->s_blocksize);
			lad->extLocation = cpu_to_lelb(epos->block);
			memset(lad->impUse, 0x00, sizeof(lad->impUse));
			break;
		}
		if (epos->bh) {
			if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
			    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
				udf_update_tag(epos->bh->b_data, loffset);
			else
				udf_update_tag(epos->bh->b_data,
						sizeof(struct allocExtDesc));
			mark_buffer_dirty_inode(epos->bh, inode);
			brelse(epos->bh);
		} else {
			mark_inode_dirty(inode);
		}
		epos->bh = nbh;
	}

	etype = udf_write_aext(inode, epos, eloc, elen, inc);

	if (!epos->bh) {
		iinfo->i_lenAlloc += adsize;
		mark_inode_dirty(inode);
	} else {
		aed = (struct allocExtDesc *)epos->bh->b_data;
		le32_add_cpu(&aed->lengthAllocDescs, adsize);
		if (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
				UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
			udf_update_tag(epos->bh->b_data,
					epos->offset + (inc ? 0 : adsize));
		else
			udf_update_tag(epos->bh->b_data,
					sizeof(struct allocExtDesc));
		mark_buffer_dirty_inode(epos->bh, inode);
	}

	return etype;
}