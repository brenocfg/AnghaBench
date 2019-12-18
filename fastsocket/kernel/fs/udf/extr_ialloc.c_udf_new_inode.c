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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct udf_sb_info {scalar_t__ s_udfrev; int /*<<< orphan*/  s_alloc_mutex; TYPE_2__* s_lvid_bh; } ;
struct TYPE_6__ {int logicalBlockNum; int /*<<< orphan*/  partitionReferenceNum; } ;
struct TYPE_4__ {void* i_data; } ;
struct udf_inode_info {int i_efe; int i_unique; int /*<<< orphan*/  i_crtime; int /*<<< orphan*/  i_alloc_type; scalar_t__ i_use; scalar_t__ i_lenAlloc; scalar_t__ i_lenEAttr; TYPE_3__ i_location; TYPE_1__ i_ext; } ;
struct super_block {scalar_t__ s_blocksize; } ;
struct logicalVolIntegrityDescImpUse {int /*<<< orphan*/  numFiles; int /*<<< orphan*/  numDirs; } ;
struct logicalVolIntegrityDesc {scalar_t__ logicalVolContentsUse; } ;
struct logicalVolHeaderDesc {int /*<<< orphan*/  uniqueID; } ;
struct inode {int i_mode; scalar_t__ i_nlink; int /*<<< orphan*/  i_flags; struct super_block* i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; scalar_t__ i_blocks; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct fileEntry {int dummy; } ;
struct extendedFileEntry {int dummy; } ;
struct TYPE_5__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int EDQUOT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICBTAG_FLAG_AD_IN_ICB ; 
 int /*<<< orphan*/  ICBTAG_FLAG_AD_LONG ; 
 int /*<<< orphan*/  ICBTAG_FLAG_AD_SHORT ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 int /*<<< orphan*/  UDF_FLAG_USE_AD_IN_ICB ; 
 int /*<<< orphan*/  UDF_FLAG_USE_EXTENDED_FE ; 
 int /*<<< orphan*/  UDF_FLAG_USE_SHORT_AD ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 scalar_t__ UDF_QUERY_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 scalar_t__ UDF_VERS_USE_EXTENDED_FE ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  current_fs_time (struct super_block*) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 void* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  udf_get_lb_pblock (struct super_block*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int udf_new_block (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 struct logicalVolIntegrityDescImpUse* udf_sb_lvidiu (struct udf_sb_info*) ; 
 int /*<<< orphan*/  udf_updated_lvid (struct super_block*) ; 
 scalar_t__ vfs_dq_alloc_inode (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_drop (struct inode*) ; 

struct inode *udf_new_inode(struct inode *dir, int mode, int *err)
{
	struct super_block *sb = dir->i_sb;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct inode *inode;
	int block;
	uint32_t start = UDF_I(dir)->i_location.logicalBlockNum;
	struct udf_inode_info *iinfo;
	struct udf_inode_info *dinfo = UDF_I(dir);

	inode = new_inode(sb);

	if (!inode) {
		*err = -ENOMEM;
		return NULL;
	}
	*err = -ENOSPC;

	iinfo = UDF_I(inode);
	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_EXTENDED_FE)) {
		iinfo->i_efe = 1;
		if (UDF_VERS_USE_EXTENDED_FE > sbi->s_udfrev)
			sbi->s_udfrev = UDF_VERS_USE_EXTENDED_FE;
		iinfo->i_ext.i_data = kzalloc(inode->i_sb->s_blocksize -
					    sizeof(struct extendedFileEntry),
					    GFP_KERNEL);
	} else {
		iinfo->i_efe = 0;
		iinfo->i_ext.i_data = kzalloc(inode->i_sb->s_blocksize -
					    sizeof(struct fileEntry),
					    GFP_KERNEL);
	}
	if (!iinfo->i_ext.i_data) {
		iput(inode);
		*err = -ENOMEM;
		return NULL;
	}

	block = udf_new_block(dir->i_sb, NULL,
			      dinfo->i_location.partitionReferenceNum,
			      start, err);
	if (*err) {
		iput(inode);
		return NULL;
	}

	mutex_lock(&sbi->s_alloc_mutex);
	if (sbi->s_lvid_bh) {
		struct logicalVolIntegrityDesc *lvid =
			(struct logicalVolIntegrityDesc *)
			sbi->s_lvid_bh->b_data;
		struct logicalVolIntegrityDescImpUse *lvidiu =
							udf_sb_lvidiu(sbi);
		struct logicalVolHeaderDesc *lvhd;
		uint64_t uniqueID;
		lvhd = (struct logicalVolHeaderDesc *)
				(lvid->logicalVolContentsUse);
		if (S_ISDIR(mode))
			le32_add_cpu(&lvidiu->numDirs, 1);
		else
			le32_add_cpu(&lvidiu->numFiles, 1);
		iinfo->i_unique = uniqueID = le64_to_cpu(lvhd->uniqueID);
		if (!(++uniqueID & 0x00000000FFFFFFFFUL))
			uniqueID += 16;
		lvhd->uniqueID = cpu_to_le64(uniqueID);
		udf_updated_lvid(sb);
	}
	mutex_unlock(&sbi->s_alloc_mutex);
	inode->i_mode = mode;
	inode->i_uid = current_fsuid();
	if (dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		if (S_ISDIR(mode))
			mode |= S_ISGID;
	} else {
		inode->i_gid = current_fsgid();
	}

	iinfo->i_location.logicalBlockNum = block;
	iinfo->i_location.partitionReferenceNum =
				dinfo->i_location.partitionReferenceNum;
	inode->i_ino = udf_get_lb_pblock(sb, &iinfo->i_location, 0);
	inode->i_blocks = 0;
	iinfo->i_lenEAttr = 0;
	iinfo->i_lenAlloc = 0;
	iinfo->i_use = 0;
	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_AD_IN_ICB))
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_IN_ICB;
	else if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_SHORT;
	else
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_LONG;
	inode->i_mtime = inode->i_atime = inode->i_ctime =
		iinfo->i_crtime = current_fs_time(inode->i_sb);
	insert_inode_hash(inode);
	mark_inode_dirty(inode);

	if (vfs_dq_alloc_inode(inode)) {
		vfs_dq_drop(inode);
		inode->i_flags |= S_NOQUOTA;
		inode->i_nlink = 0;
		iput(inode);
		*err = -EDQUOT;
		return NULL;
	}

	*err = 0;
	return inode;
}