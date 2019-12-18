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
struct super_block {int s_time_gran; struct dentry* s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; } ;
struct inode {int /*<<< orphan*/ * i_op; } ;
struct dev_data {int /*<<< orphan*/  dentry; struct super_block* sb; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GADGETFS_MAGIC ; 
 int /*<<< orphan*/  PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 struct dentry* d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  dev_init_operations ; 
 struct dev_data* dev_new () ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  gadget_fs_operations ; 
 int /*<<< orphan*/  gadgetfs_create_file (struct super_block*,int /*<<< orphan*/ ,struct dev_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct inode* gadgetfs_make_inode (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  probe_driver ; 
 int /*<<< orphan*/  put_dev (struct dev_data*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 struct dev_data* the_device ; 
 int /*<<< orphan*/  usb_gadget_register_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gadgetfs_fill_super (struct super_block *sb, void *opts, int silent)
{
	struct inode	*inode;
	struct dentry	*d;
	struct dev_data	*dev;

	if (the_device)
		return -ESRCH;

	/* fake probe to determine $CHIP */
	(void) usb_gadget_register_driver (&probe_driver);
	if (!CHIP)
		return -ENODEV;

	/* superblock */
	sb->s_blocksize = PAGE_CACHE_SIZE;
	sb->s_blocksize_bits = PAGE_CACHE_SHIFT;
	sb->s_magic = GADGETFS_MAGIC;
	sb->s_op = &gadget_fs_operations;
	sb->s_time_gran = 1;

	/* root inode */
	inode = gadgetfs_make_inode (sb,
			NULL, &simple_dir_operations,
			S_IFDIR | S_IRUGO | S_IXUGO);
	if (!inode)
		goto enomem0;
	inode->i_op = &simple_dir_inode_operations;
	if (!(d = d_alloc_root (inode)))
		goto enomem1;
	sb->s_root = d;

	/* the ep0 file is named after the controller we expect;
	 * user mode code can use it for sanity checks, like we do.
	 */
	dev = dev_new ();
	if (!dev)
		goto enomem2;

	dev->sb = sb;
	if (!gadgetfs_create_file (sb, CHIP,
				dev, &dev_init_operations,
				&dev->dentry))
		goto enomem3;

	/* other endpoint files are available after hardware setup,
	 * from binding to a controller.
	 */
	the_device = dev;
	return 0;

enomem3:
	put_dev (dev);
enomem2:
	dput (d);
enomem1:
	iput (inode);
enomem0:
	return -ENOMEM;
}