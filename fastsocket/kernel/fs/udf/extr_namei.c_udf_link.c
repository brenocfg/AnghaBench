#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct udf_fileident_bh {scalar_t__ sbh; scalar_t__ ebh; } ;
struct logicalVolIntegrityDesc {scalar_t__ logicalVolContentsUse; } ;
struct logicalVolHeaderDesc {int /*<<< orphan*/  uniqueID; } ;
struct inode {int i_nlink; int /*<<< orphan*/  i_count; TYPE_2__* i_sb; int /*<<< orphan*/  i_ctime; } ;
struct TYPE_6__ {scalar_t__ impUse; int /*<<< orphan*/  extLocation; void* extLength; } ;
struct fileIdentDesc {TYPE_1__ icb; } ;
struct dentry {struct inode* d_inode; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct allocDescImpUse {scalar_t__ impUse; } ;
typedef  void* __le32 ;
struct TYPE_9__ {scalar_t__ i_alloc_type; int /*<<< orphan*/  i_location; } ;
struct TYPE_8__ {struct buffer_head* s_lvid_bh; } ;
struct TYPE_7__ {int s_blocksize; } ;

/* Variables and functions */
 int EMLINK ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 TYPE_5__* UDF_I (struct inode*) ; 
 TYPE_3__* UDF_SB (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  cpu_to_lelb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fs_time (TYPE_2__*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct fileIdentDesc* udf_add_entry (struct inode*,struct dentry*,struct udf_fileident_bh*,struct fileIdentDesc*,int*) ; 
 int /*<<< orphan*/  udf_write_fi (struct inode*,struct fileIdentDesc*,struct fileIdentDesc*,struct udf_fileident_bh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int udf_link(struct dentry *old_dentry, struct inode *dir,
		    struct dentry *dentry)
{
	struct inode *inode = old_dentry->d_inode;
	struct udf_fileident_bh fibh;
	struct fileIdentDesc cfi, *fi;
	int err;
	struct buffer_head *bh;

	lock_kernel();
	if (inode->i_nlink >= (256 << sizeof(inode->i_nlink)) - 1) {
		unlock_kernel();
		return -EMLINK;
	}

	fi = udf_add_entry(dir, dentry, &fibh, &cfi, &err);
	if (!fi) {
		unlock_kernel();
		return err;
	}
	cfi.icb.extLength = cpu_to_le32(inode->i_sb->s_blocksize);
	cfi.icb.extLocation = cpu_to_lelb(UDF_I(inode)->i_location);
	bh = UDF_SB(inode->i_sb)->s_lvid_bh;
	if (bh) {
		struct logicalVolIntegrityDesc *lvid =
				(struct logicalVolIntegrityDesc *)bh->b_data;
		struct logicalVolHeaderDesc *lvhd;
		uint64_t uniqueID;
		lvhd = (struct logicalVolHeaderDesc *)
				(lvid->logicalVolContentsUse);
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
	inc_nlink(inode);
	inode->i_ctime = current_fs_time(inode->i_sb);
	mark_inode_dirty(inode);
	atomic_inc(&inode->i_count);
	d_instantiate(dentry, inode);
	unlock_kernel();

	return 0;
}