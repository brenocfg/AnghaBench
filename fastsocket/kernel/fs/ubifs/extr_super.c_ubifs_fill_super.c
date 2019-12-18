#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; int /*<<< orphan*/  unplug_io_fn; int /*<<< orphan*/  capabilities; } ;
struct TYPE_5__ {int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; } ;
struct ubifs_info {scalar_t__ max_inode_sz; struct inode* ubi; TYPE_2__ bdi; int /*<<< orphan*/  umount_mutex; TYPE_1__ vi; int /*<<< orphan*/  di; int /*<<< orphan*/  ltail_lnum; int /*<<< orphan*/  lhead_lnum; int /*<<< orphan*/  highest_inum; struct super_block* vfs_sb; int /*<<< orphan*/  orph_new; int /*<<< orphan*/  orph_list; int /*<<< orphan*/  old_buds; int /*<<< orphan*/  unclean_leb_list; int /*<<< orphan*/  frdi_idx_list; int /*<<< orphan*/  freeable_list; int /*<<< orphan*/  empty_list; int /*<<< orphan*/  uncat_list; int /*<<< orphan*/  replay_buds; int /*<<< orphan*/  replay_list; int /*<<< orphan*/  idx_gc; int /*<<< orphan*/  infos_list; void* orph_tree; void* size_tree; void* old_idx; void* buds; int /*<<< orphan*/  cmt_wq; int /*<<< orphan*/  bu_mutex; int /*<<< orphan*/  mst_mutex; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  tnc_mutex; int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  commit_sem; int /*<<< orphan*/  orphan_lock; int /*<<< orphan*/  space_lock; int /*<<< orphan*/  buds_lock; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/  cnt_lock; } ;
struct ubi_volume_desc {scalar_t__ max_inode_sz; struct inode* ubi; TYPE_2__ bdi; int /*<<< orphan*/  umount_mutex; TYPE_1__ vi; int /*<<< orphan*/  di; int /*<<< orphan*/  ltail_lnum; int /*<<< orphan*/  lhead_lnum; int /*<<< orphan*/  highest_inum; struct super_block* vfs_sb; int /*<<< orphan*/  orph_new; int /*<<< orphan*/  orph_list; int /*<<< orphan*/  old_buds; int /*<<< orphan*/  unclean_leb_list; int /*<<< orphan*/  frdi_idx_list; int /*<<< orphan*/  freeable_list; int /*<<< orphan*/  empty_list; int /*<<< orphan*/  uncat_list; int /*<<< orphan*/  replay_buds; int /*<<< orphan*/  replay_list; int /*<<< orphan*/  idx_gc; int /*<<< orphan*/  infos_list; void* orph_tree; void* size_tree; void* old_idx; void* buds; int /*<<< orphan*/  cmt_wq; int /*<<< orphan*/  bu_mutex; int /*<<< orphan*/  mst_mutex; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  tnc_mutex; int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  commit_sem; int /*<<< orphan*/  orphan_lock; int /*<<< orphan*/  space_lock; int /*<<< orphan*/  buds_lock; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/  cnt_lock; } ;
struct super_block {scalar_t__ s_maxbytes; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_magic; struct ubifs_info* s_fs_info; TYPE_2__* s_bdi; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_CAP_MAP_COPY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ MAX_LFS_FILESIZE ; 
 int PTR_ERR (struct inode*) ; 
 void* RB_ROOT ; 
 int /*<<< orphan*/  UBIFS_BLOCK_SHIFT ; 
 int /*<<< orphan*/  UBIFS_BLOCK_SIZE ; 
 int /*<<< orphan*/  UBIFS_FIRST_INO ; 
 int /*<<< orphan*/  UBIFS_LOG_LNUM ; 
 int /*<<< orphan*/  UBIFS_ROOT_INO ; 
 int /*<<< orphan*/  UBIFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  UBI_READWRITE ; 
 int /*<<< orphan*/  bdi_destroy (TYPE_2__*) ; 
 int bdi_init (TYPE_2__*) ; 
 int bdi_register (TYPE_2__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  default_unplug_io_fn ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ key_max_inode_size (struct ubifs_info*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_info*) ; 
 struct ubifs_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mount_ubifs (struct ubifs_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_close_volume (struct inode*) ; 
 int /*<<< orphan*/  ubi_get_device_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_get_volume_info (struct ubifs_info*,TYPE_1__*) ; 
 struct inode* ubi_open_volume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 struct inode* ubifs_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int ubifs_parse_options (struct ubifs_info*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_super_operations ; 
 int /*<<< orphan*/  ubifs_umount (struct ubifs_info*) ; 

__attribute__((used)) static int ubifs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct ubi_volume_desc *ubi = sb->s_fs_info;
	struct ubifs_info *c;
	struct inode *root;
	int err;

	c = kzalloc(sizeof(struct ubifs_info), GFP_KERNEL);
	if (!c)
		return -ENOMEM;

	spin_lock_init(&c->cnt_lock);
	spin_lock_init(&c->cs_lock);
	spin_lock_init(&c->buds_lock);
	spin_lock_init(&c->space_lock);
	spin_lock_init(&c->orphan_lock);
	init_rwsem(&c->commit_sem);
	mutex_init(&c->lp_mutex);
	mutex_init(&c->tnc_mutex);
	mutex_init(&c->log_mutex);
	mutex_init(&c->mst_mutex);
	mutex_init(&c->umount_mutex);
	mutex_init(&c->bu_mutex);
	init_waitqueue_head(&c->cmt_wq);
	c->buds = RB_ROOT;
	c->old_idx = RB_ROOT;
	c->size_tree = RB_ROOT;
	c->orph_tree = RB_ROOT;
	INIT_LIST_HEAD(&c->infos_list);
	INIT_LIST_HEAD(&c->idx_gc);
	INIT_LIST_HEAD(&c->replay_list);
	INIT_LIST_HEAD(&c->replay_buds);
	INIT_LIST_HEAD(&c->uncat_list);
	INIT_LIST_HEAD(&c->empty_list);
	INIT_LIST_HEAD(&c->freeable_list);
	INIT_LIST_HEAD(&c->frdi_idx_list);
	INIT_LIST_HEAD(&c->unclean_leb_list);
	INIT_LIST_HEAD(&c->old_buds);
	INIT_LIST_HEAD(&c->orph_list);
	INIT_LIST_HEAD(&c->orph_new);

	c->vfs_sb = sb;
	c->highest_inum = UBIFS_FIRST_INO;
	c->lhead_lnum = c->ltail_lnum = UBIFS_LOG_LNUM;

	ubi_get_volume_info(ubi, &c->vi);
	ubi_get_device_info(c->vi.ubi_num, &c->di);

	/* Re-open the UBI device in read-write mode */
	c->ubi = ubi_open_volume(c->vi.ubi_num, c->vi.vol_id, UBI_READWRITE);
	if (IS_ERR(c->ubi)) {
		err = PTR_ERR(c->ubi);
		goto out_free;
	}

	/*
	 * UBIFS provides 'backing_dev_info' in order to disable read-ahead. For
	 * UBIFS, I/O is not deferred, it is done immediately in readpage,
	 * which means the user would have to wait not just for their own I/O
	 * but the read-ahead I/O as well i.e. completely pointless.
	 *
	 * Read-ahead will be disabled because @c->bdi.ra_pages is 0.
	 */
	c->bdi.name = "ubifs",
	c->bdi.capabilities = BDI_CAP_MAP_COPY;
	c->bdi.unplug_io_fn = default_unplug_io_fn;
	err  = bdi_init(&c->bdi);
	if (err)
		goto out_close;
	err = bdi_register(&c->bdi, NULL, "ubifs_%d_%d",
			   c->vi.ubi_num, c->vi.vol_id);
	if (err)
		goto out_bdi;

	err = ubifs_parse_options(c, data, 0);
	if (err)
		goto out_bdi;

	sb->s_bdi = &c->bdi;
	sb->s_fs_info = c;
	sb->s_magic = UBIFS_SUPER_MAGIC;
	sb->s_blocksize = UBIFS_BLOCK_SIZE;
	sb->s_blocksize_bits = UBIFS_BLOCK_SHIFT;
	sb->s_maxbytes = c->max_inode_sz = key_max_inode_size(c);
	if (c->max_inode_sz > MAX_LFS_FILESIZE)
		sb->s_maxbytes = c->max_inode_sz = MAX_LFS_FILESIZE;
	sb->s_op = &ubifs_super_operations;

	mutex_lock(&c->umount_mutex);
	err = mount_ubifs(c);
	if (err) {
		ubifs_assert(err < 0);
		goto out_unlock;
	}

	/* Read the root inode */
	root = ubifs_iget(sb, UBIFS_ROOT_INO);
	if (IS_ERR(root)) {
		err = PTR_ERR(root);
		goto out_umount;
	}

	sb->s_root = d_alloc_root(root);
	if (!sb->s_root)
		goto out_iput;

	mutex_unlock(&c->umount_mutex);
	return 0;

out_iput:
	iput(root);
out_umount:
	ubifs_umount(c);
out_unlock:
	mutex_unlock(&c->umount_mutex);
out_bdi:
	bdi_destroy(&c->bdi);
out_close:
	ubi_close_volume(c->ubi);
out_free:
	kfree(c);
	return err;
}