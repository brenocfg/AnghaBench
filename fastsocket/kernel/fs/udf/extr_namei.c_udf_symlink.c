#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_17__ {int /*<<< orphan*/  partitionReferenceNum; int /*<<< orphan*/  logicalBlockNum; } ;
struct TYPE_21__ {char* i_data; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; int i_lenExtents; int i_lenEAttr; int i_lenAlloc; TYPE_13__ i_location; TYPE_3__ i_ext; } ;
struct udf_fileident_bh {TYPE_4__* sbh; TYPE_4__* ebh; } ;
struct pathComponent {int componentType; int lengthComponentIdent; int /*<<< orphan*/  componentIdent; scalar_t__ componentFileVersionNum; } ;
struct logicalVolIntegrityDesc {scalar_t__ logicalVolContentsUse; } ;
struct logicalVolHeaderDesc {int /*<<< orphan*/  uniqueID; } ;
struct kernel_lb_addr {int logicalBlockNum; int /*<<< orphan*/  partitionReferenceNum; } ;
struct TYPE_20__ {int /*<<< orphan*/ * a_ops; } ;
struct inode {int i_mode; int i_size; TYPE_6__* i_sb; int /*<<< orphan*/ * i_op; TYPE_2__ i_data; } ;
struct TYPE_19__ {scalar_t__ impUse; int /*<<< orphan*/  extLocation; void* extLength; } ;
struct fileIdentDesc {TYPE_1__ icb; } ;
struct extent_position {TYPE_4__* bh; int /*<<< orphan*/  offset; TYPE_13__ block; } ;
struct dentry {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct allocDescImpUse {scalar_t__ impUse; } ;
typedef  void* __le32 ;
struct TYPE_23__ {int s_blocksize; } ;
struct TYPE_22__ {char* b_data; } ;
struct TYPE_18__ {struct buffer_head* s_lvid_bh; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  UDF_NAME_LEN ; 
 TYPE_15__* UDF_SB (TYPE_6__*) ; 
 int /*<<< orphan*/  brelse (TYPE_4__*) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  cpu_to_lelb (TYPE_13__) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (TYPE_4__*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 
 int /*<<< orphan*/  set_buffer_uptodate (TYPE_4__*) ; 
 int /*<<< orphan*/  udf_add_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,int /*<<< orphan*/ ) ; 
 struct fileIdentDesc* udf_add_entry (struct inode*,struct dentry*,struct udf_fileident_bh*,struct fileIdentDesc*,int*) ; 
 int udf_ext0_offset (struct inode*) ; 
 int /*<<< orphan*/  udf_file_entry_alloc_offset (struct inode*) ; 
 int udf_get_pblock (TYPE_6__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int udf_new_block (TYPE_6__*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct inode* udf_new_inode (struct inode*,int,int*) ; 
 int udf_put_filename (TYPE_6__*,char*,char*,int) ; 
 int /*<<< orphan*/  udf_symlink_aops ; 
 TYPE_4__* udf_tread (TYPE_6__*,int) ; 
 int /*<<< orphan*/  udf_write_fi (struct inode*,struct fileIdentDesc*,struct fileIdentDesc*,struct udf_fileident_bh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int udf_symlink(struct inode *dir, struct dentry *dentry,
		       const char *symname)
{
	struct inode *inode;
	struct pathComponent *pc;
	char *compstart;
	struct udf_fileident_bh fibh;
	struct extent_position epos = {};
	int eoffset, elen = 0;
	struct fileIdentDesc *fi;
	struct fileIdentDesc cfi;
	char *ea;
	int err;
	int block;
	char *name = NULL;
	int namelen;
	struct buffer_head *bh;
	struct udf_inode_info *iinfo;

	lock_kernel();
	inode = udf_new_inode(dir, S_IFLNK, &err);
	if (!inode)
		goto out;

	name = kmalloc(UDF_NAME_LEN, GFP_NOFS);
	if (!name) {
		err = -ENOMEM;
		goto out_no_entry;
	}

	iinfo = UDF_I(inode);
	inode->i_mode = S_IFLNK | S_IRWXUGO;
	inode->i_data.a_ops = &udf_symlink_aops;
	inode->i_op = &page_symlink_inode_operations;

	if (iinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) {
		struct kernel_lb_addr eloc;
		uint32_t bsize;

		block = udf_new_block(inode->i_sb, inode,
				iinfo->i_location.partitionReferenceNum,
				iinfo->i_location.logicalBlockNum, &err);
		if (!block)
			goto out_no_entry;
		epos.block = iinfo->i_location;
		epos.offset = udf_file_entry_alloc_offset(inode);
		epos.bh = NULL;
		eloc.logicalBlockNum = block;
		eloc.partitionReferenceNum =
				iinfo->i_location.partitionReferenceNum;
		bsize = inode->i_sb->s_blocksize;
		iinfo->i_lenExtents = bsize;
		udf_add_aext(inode, &epos, &eloc, bsize, 0);
		brelse(epos.bh);

		block = udf_get_pblock(inode->i_sb, block,
				iinfo->i_location.partitionReferenceNum,
				0);
		epos.bh = udf_tread(inode->i_sb, block);
		lock_buffer(epos.bh);
		memset(epos.bh->b_data, 0x00, inode->i_sb->s_blocksize);
		set_buffer_uptodate(epos.bh);
		unlock_buffer(epos.bh);
		mark_buffer_dirty_inode(epos.bh, inode);
		ea = epos.bh->b_data + udf_ext0_offset(inode);
	} else
		ea = iinfo->i_ext.i_data + iinfo->i_lenEAttr;

	eoffset = inode->i_sb->s_blocksize - udf_ext0_offset(inode);
	pc = (struct pathComponent *)ea;

	if (*symname == '/') {
		do {
			symname++;
		} while (*symname == '/');

		pc->componentType = 1;
		pc->lengthComponentIdent = 0;
		pc->componentFileVersionNum = 0;
		elen += sizeof(struct pathComponent);
	}

	err = -ENAMETOOLONG;

	while (*symname) {
		if (elen + sizeof(struct pathComponent) > eoffset)
			goto out_no_entry;

		pc = (struct pathComponent *)(ea + elen);

		compstart = (char *)symname;

		do {
			symname++;
		} while (*symname && *symname != '/');

		pc->componentType = 5;
		pc->lengthComponentIdent = 0;
		pc->componentFileVersionNum = 0;
		if (compstart[0] == '.') {
			if ((symname - compstart) == 1)
				pc->componentType = 4;
			else if ((symname - compstart) == 2 &&
					compstart[1] == '.')
				pc->componentType = 3;
		}

		if (pc->componentType == 5) {
			namelen = udf_put_filename(inode->i_sb, compstart, name,
						   symname - compstart);
			if (!namelen)
				goto out_no_entry;

			if (elen + sizeof(struct pathComponent) + namelen >
					eoffset)
				goto out_no_entry;
			else
				pc->lengthComponentIdent = namelen;

			memcpy(pc->componentIdent, name, namelen);
		}

		elen += sizeof(struct pathComponent) + pc->lengthComponentIdent;

		if (*symname) {
			do {
				symname++;
			} while (*symname == '/');
		}
	}

	brelse(epos.bh);
	inode->i_size = elen;
	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		iinfo->i_lenAlloc = inode->i_size;
	mark_inode_dirty(inode);

	fi = udf_add_entry(dir, dentry, &fibh, &cfi, &err);
	if (!fi)
		goto out_no_entry;
	cfi.icb.extLength = cpu_to_le32(inode->i_sb->s_blocksize);
	cfi.icb.extLocation = cpu_to_lelb(iinfo->i_location);
	bh = UDF_SB(inode->i_sb)->s_lvid_bh;
	if (bh) {
		struct logicalVolIntegrityDesc *lvid =
				(struct logicalVolIntegrityDesc *)bh->b_data;
		struct logicalVolHeaderDesc *lvhd;
		uint64_t uniqueID;
		lvhd = (struct logicalVolHeaderDesc *)
				lvid->logicalVolContentsUse;
		uniqueID = le64_to_cpu(lvhd->uniqueID);
		*(__le32 *)((struct allocDescImpUse *)cfi.icb.impUse)->impUse =
			cpu_to_le32(uniqueID & 0x00000000FFFFFFFFUL);
		if (!(++uniqueID & 0x00000000FFFFFFFFUL))
			uniqueID += 16;
		lvhd->uniqueID = cpu_to_le64(uniqueID);
		mark_buffer_dirty(bh);
	}
	udf_write_fi(dir, &cfi, fi, &fibh, NULL, NULL);
	if (UDF_I(dir)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		mark_inode_dirty(dir);
	if (fibh.sbh != fibh.ebh)
		brelse(fibh.ebh);
	brelse(fibh.sbh);
	d_instantiate(dentry, inode);
	err = 0;

out:
	kfree(name);
	unlock_kernel();
	return err;

out_no_entry:
	inode_dec_link_count(inode);
	iput(inode);
	goto out;
}