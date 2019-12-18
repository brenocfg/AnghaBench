#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  partitionReferenceNum; int /*<<< orphan*/  logicalBlockNum; } ;
struct TYPE_9__ {int i_data; } ;
struct udf_inode_info {int i_lenEAttr; int i_lenAlloc; int i_lenExtents; TYPE_3__ i_location; TYPE_2__ i_ext; void* i_alloc_type; } ;
struct udf_fileident_bh {int soffset; int eoffset; struct buffer_head* ebh; struct buffer_head* sbh; } ;
struct kernel_lb_addr {int logicalBlockNum; int /*<<< orphan*/  partitionReferenceNum; } ;
struct inode {int i_size; TYPE_4__* i_sb; } ;
struct TYPE_8__ {int /*<<< orphan*/  tagLocation; } ;
struct fileIdentDesc {int /*<<< orphan*/  lengthOfImpUse; scalar_t__ fileIdent; int /*<<< orphan*/  impUse; TYPE_1__ descTag; } ;
struct extent_position {struct buffer_head* bh; int /*<<< orphan*/  offset; TYPE_3__ block; } ;
struct buffer_head {int b_data; } ;
typedef  int loff_t ;
struct TYPE_11__ {int s_blocksize; } ;

/* Variables and functions */
 void* ICBTAG_FLAG_AD_IN_ICB ; 
 void* ICBTAG_FLAG_AD_LONG ; 
 void* ICBTAG_FLAG_AD_SHORT ; 
 int /*<<< orphan*/  UDF_FLAG_USE_SHORT_AD ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 scalar_t__ UDF_QUERY_FLAG (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (int,int,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  udf_add_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,int /*<<< orphan*/ ) ; 
 int udf_ext0_offset (struct inode*) ; 
 int /*<<< orphan*/  udf_file_entry_alloc_offset (struct inode*) ; 
 struct fileIdentDesc* udf_fileident_read (struct inode*,int*,struct udf_fileident_bh*,struct fileIdentDesc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int udf_get_pblock (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int udf_new_block (TYPE_4__*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct buffer_head* udf_tgetblk (TYPE_4__*,int) ; 
 scalar_t__ udf_write_fi (struct inode*,struct fileIdentDesc*,struct fileIdentDesc*,struct udf_fileident_bh*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

struct buffer_head *udf_expand_dir_adinicb(struct inode *inode, int *block,
					   int *err)
{
	int newblock;
	struct buffer_head *dbh = NULL;
	struct kernel_lb_addr eloc;
	uint32_t elen;
	uint8_t alloctype;
	struct extent_position epos;

	struct udf_fileident_bh sfibh, dfibh;
	loff_t f_pos = udf_ext0_offset(inode);
	int size = udf_ext0_offset(inode) + inode->i_size;
	struct fileIdentDesc cfi, *sfi, *dfi;
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
		alloctype = ICBTAG_FLAG_AD_SHORT;
	else
		alloctype = ICBTAG_FLAG_AD_LONG;

	if (!inode->i_size) {
		iinfo->i_alloc_type = alloctype;
		mark_inode_dirty(inode);
		return NULL;
	}

	/* alloc block, and copy data to it */
	*block = udf_new_block(inode->i_sb, inode,
			       iinfo->i_location.partitionReferenceNum,
			       iinfo->i_location.logicalBlockNum, err);
	if (!(*block))
		return NULL;
	newblock = udf_get_pblock(inode->i_sb, *block,
				  iinfo->i_location.partitionReferenceNum,
				0);
	if (!newblock)
		return NULL;
	dbh = udf_tgetblk(inode->i_sb, newblock);
	if (!dbh)
		return NULL;
	lock_buffer(dbh);
	memset(dbh->b_data, 0x00, inode->i_sb->s_blocksize);
	set_buffer_uptodate(dbh);
	unlock_buffer(dbh);
	mark_buffer_dirty_inode(dbh, inode);

	sfibh.soffset = sfibh.eoffset =
			f_pos & (inode->i_sb->s_blocksize - 1);
	sfibh.sbh = sfibh.ebh = NULL;
	dfibh.soffset = dfibh.eoffset = 0;
	dfibh.sbh = dfibh.ebh = dbh;
	while (f_pos < size) {
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_IN_ICB;
		sfi = udf_fileident_read(inode, &f_pos, &sfibh, &cfi, NULL,
					 NULL, NULL, NULL);
		if (!sfi) {
			brelse(dbh);
			return NULL;
		}
		iinfo->i_alloc_type = alloctype;
		sfi->descTag.tagLocation = cpu_to_le32(*block);
		dfibh.soffset = dfibh.eoffset;
		dfibh.eoffset += (sfibh.eoffset - sfibh.soffset);
		dfi = (struct fileIdentDesc *)(dbh->b_data + dfibh.soffset);
		if (udf_write_fi(inode, sfi, dfi, &dfibh, sfi->impUse,
				 sfi->fileIdent +
					le16_to_cpu(sfi->lengthOfImpUse))) {
			iinfo->i_alloc_type = ICBTAG_FLAG_AD_IN_ICB;
			brelse(dbh);
			return NULL;
		}
	}
	mark_buffer_dirty_inode(dbh, inode);

	memset(iinfo->i_ext.i_data + iinfo->i_lenEAttr, 0,
		iinfo->i_lenAlloc);
	iinfo->i_lenAlloc = 0;
	eloc.logicalBlockNum = *block;
	eloc.partitionReferenceNum =
				iinfo->i_location.partitionReferenceNum;
	elen = inode->i_sb->s_blocksize;
	iinfo->i_lenExtents = elen;
	epos.bh = NULL;
	epos.block = iinfo->i_location;
	epos.offset = udf_file_entry_alloc_offset(inode);
	udf_add_aext(inode, &epos, &eloc, elen, 0);
	/* UniqueID stuff */

	brelse(epos.bh);
	mark_inode_dirty(inode);
	return dbh;
}