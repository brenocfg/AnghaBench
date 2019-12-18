#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ocfs2_super {int s_mount_opt; int fs_generation; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_rdev; } ;
struct TYPE_9__ {TYPE_1__ dev1; } ;
struct ocfs2_dinode {int i_flags; int i_fs_generation; int i_clusters; int i_attr; int i_generation; int i_uid; int i_gid; int i_atime_nsec; int i_mtime_nsec; int i_ctime_nsec; int /*<<< orphan*/  i_blkno; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mode; TYPE_2__ id1; int /*<<< orphan*/  i_dyn_features; } ;
struct TYPE_13__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_12__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_11__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct inode {int i_version; int i_generation; int i_mode; int i_uid; int i_gid; struct super_block* i_sb; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_nlink; TYPE_6__ i_ctime; TYPE_5__ i_mtime; TYPE_4__ i_atime; TYPE_3__* i_mapping; scalar_t__ i_blocks; } ;
struct TYPE_14__ {int ip_clusters; int ip_attr; scalar_t__ ip_blkno; scalar_t__ ip_last_used_group; scalar_t__ ip_last_used_slot; int /*<<< orphan*/  ip_rw_lockres; int /*<<< orphan*/  ip_open_lockres; int /*<<< orphan*/  ip_inode_lockres; int /*<<< orphan*/  ip_flags; void* ip_dyn_features; } ;
struct TYPE_10__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int OCFS2_BITMAP_FL ; 
 TYPE_7__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INODE_BITMAP ; 
 int /*<<< orphan*/  OCFS2_INODE_SYSTEM_FILE ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DINODE (struct ocfs2_dinode*) ; 
 int OCFS2_LOCAL_ALLOC_FL ; 
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_META ; 
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_OPEN ; 
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_RW ; 
 int OCFS2_MOUNT_LOCALFLOCKS ; 
 int OCFS2_QUOTA_FL ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int OCFS2_SUPER_BLOCK_FL ; 
 int OCFS2_SYSTEM_FL ; 
 int OCFS2_VALID_FL ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 scalar_t__ S_ISLNK (int) ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  huge_decode_dev (scalar_t__) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_from_blkno (struct super_block*,scalar_t__) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct inode*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  ocfs2_aops ; 
 int /*<<< orphan*/  ocfs2_dir_iops ; 
 int /*<<< orphan*/  ocfs2_dops ; 
 int /*<<< orphan*/  ocfs2_dops_no_plocks ; 
 int /*<<< orphan*/  ocfs2_fast_symlink_inode_operations ; 
 int /*<<< orphan*/  ocfs2_file_iops ; 
 int /*<<< orphan*/  ocfs2_fops ; 
 int /*<<< orphan*/  ocfs2_fops_no_plocks ; 
 int /*<<< orphan*/  ocfs2_inode_is_fast_symlink (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_inode_lock_res_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct inode*) ; 
 scalar_t__ ocfs2_inode_sector_count (struct inode*) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_read_links_count (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_special_file_iops ; 
 int /*<<< orphan*/  ocfs2_stack_supports_plocks () ; 
 int /*<<< orphan*/  ocfs2_symlink_inode_operations ; 

void ocfs2_populate_inode(struct inode *inode, struct ocfs2_dinode *fe,
			  int create_ino)
{
	struct super_block *sb;
	struct ocfs2_super *osb;
	int use_plocks = 1;

	mlog_entry("(0x%p, size:%llu)\n", inode,
		   (unsigned long long)le64_to_cpu(fe->i_size));

	sb = inode->i_sb;
	osb = OCFS2_SB(sb);

	if ((osb->s_mount_opt & OCFS2_MOUNT_LOCALFLOCKS) ||
	    ocfs2_mount_local(osb) || !ocfs2_stack_supports_plocks())
		use_plocks = 0;

	/*
	 * These have all been checked by ocfs2_read_inode_block() or set
	 * by ocfs2_mknod_locked(), so a failure is a code bug.
	 */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));  /* This means that read_inode
						cannot create a superblock
						inode today.  change if
						that is needed. */
	BUG_ON(!(fe->i_flags & cpu_to_le32(OCFS2_VALID_FL)));
	BUG_ON(le32_to_cpu(fe->i_fs_generation) != osb->fs_generation);


	OCFS2_I(inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	OCFS2_I(inode)->ip_attr = le32_to_cpu(fe->i_attr);
	OCFS2_I(inode)->ip_dyn_features = le16_to_cpu(fe->i_dyn_features);

	inode->i_version = 1;
	inode->i_generation = le32_to_cpu(fe->i_generation);
	inode->i_rdev = huge_decode_dev(le64_to_cpu(fe->id1.dev1.i_rdev));
	inode->i_mode = le16_to_cpu(fe->i_mode);
	inode->i_uid = le32_to_cpu(fe->i_uid);
	inode->i_gid = le32_to_cpu(fe->i_gid);

	/* Fast symlinks will have i_size but no allocated clusters. */
	if (S_ISLNK(inode->i_mode) && !fe->i_clusters)
		inode->i_blocks = 0;
	else
		inode->i_blocks = ocfs2_inode_sector_count(inode);
	inode->i_mapping->a_ops = &ocfs2_aops;
	inode->i_atime.tv_sec = le64_to_cpu(fe->i_atime);
	inode->i_atime.tv_nsec = le32_to_cpu(fe->i_atime_nsec);
	inode->i_mtime.tv_sec = le64_to_cpu(fe->i_mtime);
	inode->i_mtime.tv_nsec = le32_to_cpu(fe->i_mtime_nsec);
	inode->i_ctime.tv_sec = le64_to_cpu(fe->i_ctime);
	inode->i_ctime.tv_nsec = le32_to_cpu(fe->i_ctime_nsec);

	if (OCFS2_I(inode)->ip_blkno != le64_to_cpu(fe->i_blkno))
		mlog(ML_ERROR,
		     "ip_blkno %llu != i_blkno %llu!\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno,
		     (unsigned long long)le64_to_cpu(fe->i_blkno));

	inode->i_nlink = ocfs2_read_links_count(fe);

	if (fe->i_flags & cpu_to_le32(OCFS2_SYSTEM_FL)) {
		OCFS2_I(inode)->ip_flags |= OCFS2_INODE_SYSTEM_FILE;
		inode->i_flags |= S_NOQUOTA;
	}

	if (fe->i_flags & cpu_to_le32(OCFS2_LOCAL_ALLOC_FL)) {
		OCFS2_I(inode)->ip_flags |= OCFS2_INODE_BITMAP;
		mlog(0, "local alloc inode: i_ino=%lu\n", inode->i_ino);
	} else if (fe->i_flags & cpu_to_le32(OCFS2_BITMAP_FL)) {
		OCFS2_I(inode)->ip_flags |= OCFS2_INODE_BITMAP;
	} else if (fe->i_flags & cpu_to_le32(OCFS2_QUOTA_FL)) {
		inode->i_flags |= S_NOQUOTA;
	} else if (fe->i_flags & cpu_to_le32(OCFS2_SUPER_BLOCK_FL)) {
		mlog(0, "superblock inode: i_ino=%lu\n", inode->i_ino);
		/* we can't actually hit this as read_inode can't
		 * handle superblocks today ;-) */
		BUG();
	}

	switch (inode->i_mode & S_IFMT) {
	    case S_IFREG:
		    if (use_plocks)
			    inode->i_fop = &ocfs2_fops;
		    else
			    inode->i_fop = &ocfs2_fops_no_plocks;
		    inode->i_op = &ocfs2_file_iops;
		    i_size_write(inode, le64_to_cpu(fe->i_size));
		    break;
	    case S_IFDIR:
		    inode->i_op = &ocfs2_dir_iops;
		    if (use_plocks)
			    inode->i_fop = &ocfs2_dops;
		    else
			    inode->i_fop = &ocfs2_dops_no_plocks;
		    i_size_write(inode, le64_to_cpu(fe->i_size));
		    break;
	    case S_IFLNK:
		    if (ocfs2_inode_is_fast_symlink(inode))
			inode->i_op = &ocfs2_fast_symlink_inode_operations;
		    else
			inode->i_op = &ocfs2_symlink_inode_operations;
		    i_size_write(inode, le64_to_cpu(fe->i_size));
		    break;
	    default:
		    inode->i_op = &ocfs2_special_file_iops;
		    init_special_inode(inode, inode->i_mode,
				       inode->i_rdev);
		    break;
	}

	if (create_ino) {
		inode->i_ino = ino_from_blkno(inode->i_sb,
			       le64_to_cpu(fe->i_blkno));

		/*
		 * If we ever want to create system files from kernel,
		 * the generation argument to
		 * ocfs2_inode_lock_res_init() will have to change.
		 */
		BUG_ON(le32_to_cpu(fe->i_flags) & OCFS2_SYSTEM_FL);

		ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_inode_lockres,
					  OCFS2_LOCK_TYPE_META, 0, inode);

		ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_open_lockres,
					  OCFS2_LOCK_TYPE_OPEN, 0, inode);
	}

	ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_rw_lockres,
				  OCFS2_LOCK_TYPE_RW, inode->i_generation,
				  inode);

	ocfs2_set_inode_flags(inode);

	OCFS2_I(inode)->ip_last_used_slot = 0;
	OCFS2_I(inode)->ip_last_used_group = 0;
	mlog_exit_void();
}