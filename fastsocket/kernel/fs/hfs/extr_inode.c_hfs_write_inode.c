#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct inode {int i_ino; int i_mode; int /*<<< orphan*/  i_mtime; scalar_t__ i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_nlink; } ;
struct hfs_find_data {int entrylength; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; TYPE_1__* search_key; } ;
struct hfs_cat_file {int dummy; } ;
struct hfs_cat_dir {int dummy; } ;
struct TYPE_11__ {void* MdDat; int /*<<< orphan*/  PyLen; int /*<<< orphan*/  LgLen; int /*<<< orphan*/  ExtRec; int /*<<< orphan*/  Flags; int /*<<< orphan*/  FlNum; int /*<<< orphan*/  RPyLen; int /*<<< orphan*/  RLgLen; int /*<<< orphan*/  RExtRec; } ;
struct TYPE_10__ {int /*<<< orphan*/  Val; void* MdDat; int /*<<< orphan*/  DirID; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_3__ file; TYPE_2__ dir; } ;
typedef  TYPE_4__ hfs_cat_rec ;
struct TYPE_14__ {int /*<<< orphan*/  cat_key; struct inode* rsrc_inode; } ;
struct TYPE_13__ {int /*<<< orphan*/  cat_tree; int /*<<< orphan*/  ext_tree; } ;
struct TYPE_9__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DBG_INODE ; 
 int EIO ; 
#define  HFS_CAT_CNID 130 
 scalar_t__ HFS_CDR_DIR ; 
 scalar_t__ HFS_CDR_FIL ; 
#define  HFS_EXT_CNID 129 
 int /*<<< orphan*/  HFS_FIL_LOCK ; 
 int HFS_FIRSTUSER_CNID ; 
 TYPE_8__* HFS_I (struct inode*) ; 
 scalar_t__ HFS_IS_RSRC (struct inode*) ; 
#define  HFS_ROOT_CNID 128 
 TYPE_7__* HFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_IWUSR ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hfs_bnode_write (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hfs_brec_find (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_btree_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_ext_write_extent (struct inode*) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 scalar_t__ hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_inode_write_fork (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* hfs_u_to_mtime (int /*<<< orphan*/ ) ; 

int hfs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	struct inode *main_inode = inode;
	struct hfs_find_data fd;
	hfs_cat_rec rec;

	dprint(DBG_INODE, "hfs_write_inode: %lu\n", inode->i_ino);
	hfs_ext_write_extent(inode);

	if (inode->i_ino < HFS_FIRSTUSER_CNID) {
		switch (inode->i_ino) {
		case HFS_ROOT_CNID:
			break;
		case HFS_EXT_CNID:
			hfs_btree_write(HFS_SB(inode->i_sb)->ext_tree);
			return 0;
		case HFS_CAT_CNID:
			hfs_btree_write(HFS_SB(inode->i_sb)->cat_tree);
			return 0;
		default:
			BUG();
			return -EIO;
		}
	}

	if (HFS_IS_RSRC(inode))
		main_inode = HFS_I(inode)->rsrc_inode;

	if (!main_inode->i_nlink)
		return 0;

	if (hfs_find_init(HFS_SB(main_inode->i_sb)->cat_tree, &fd))
		/* panic? */
		return -EIO;

	fd.search_key->cat = HFS_I(main_inode)->cat_key;
	if (hfs_brec_find(&fd))
		/* panic? */
		goto out;

	if (S_ISDIR(main_inode->i_mode)) {
		if (fd.entrylength < sizeof(struct hfs_cat_dir))
			/* panic? */;
		hfs_bnode_read(fd.bnode, &rec, fd.entryoffset,
			   sizeof(struct hfs_cat_dir));
		if (rec.type != HFS_CDR_DIR ||
		    be32_to_cpu(rec.dir.DirID) != inode->i_ino) {
		}

		rec.dir.MdDat = hfs_u_to_mtime(inode->i_mtime);
		rec.dir.Val = cpu_to_be16(inode->i_size - 2);

		hfs_bnode_write(fd.bnode, &rec, fd.entryoffset,
			    sizeof(struct hfs_cat_dir));
	} else if (HFS_IS_RSRC(inode)) {
		hfs_bnode_read(fd.bnode, &rec, fd.entryoffset,
			       sizeof(struct hfs_cat_file));
		hfs_inode_write_fork(inode, rec.file.RExtRec,
				     &rec.file.RLgLen, &rec.file.RPyLen);
		hfs_bnode_write(fd.bnode, &rec, fd.entryoffset,
				sizeof(struct hfs_cat_file));
	} else {
		if (fd.entrylength < sizeof(struct hfs_cat_file))
			/* panic? */;
		hfs_bnode_read(fd.bnode, &rec, fd.entryoffset,
			   sizeof(struct hfs_cat_file));
		if (rec.type != HFS_CDR_FIL ||
		    be32_to_cpu(rec.file.FlNum) != inode->i_ino) {
		}

		if (inode->i_mode & S_IWUSR)
			rec.file.Flags &= ~HFS_FIL_LOCK;
		else
			rec.file.Flags |= HFS_FIL_LOCK;
		hfs_inode_write_fork(inode, rec.file.ExtRec, &rec.file.LgLen, &rec.file.PyLen);
		rec.file.MdDat = hfs_u_to_mtime(inode->i_mtime);

		hfs_bnode_write(fd.bnode, &rec, fd.entryoffset,
			    sizeof(struct hfs_cat_file));
	}
out:
	hfs_find_exit(&fd);
	return 0;
}