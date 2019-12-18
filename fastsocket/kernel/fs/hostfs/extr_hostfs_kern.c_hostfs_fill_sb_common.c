#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_blocksize; int s_blocksize_bits; int /*<<< orphan*/ * s_root; int /*<<< orphan*/  s_maxbytes; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {char* host_filename; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* HOSTFS_I (struct inode*) ; 
 int /*<<< orphan*/  HOSTFS_SUPER_MAGIC ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/ * d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ *) ; 
 struct inode* hostfs_iget (struct super_block*) ; 
 int hostfs_read_inode (struct inode*) ; 
 int /*<<< orphan*/  hostfs_sbops ; 
 int init_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 char* root_ino ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int hostfs_fill_sb_common(struct super_block *sb, void *d, int silent)
{
	struct inode *root_inode;
	char *host_root_path, *req_root = d;
	int err;

	sb->s_blocksize = 1024;
	sb->s_blocksize_bits = 10;
	sb->s_magic = HOSTFS_SUPER_MAGIC;
	sb->s_op = &hostfs_sbops;
	sb->s_maxbytes = MAX_LFS_FILESIZE;

	/* NULL is printed as <NULL> by sprintf: avoid that. */
	if (req_root == NULL)
		req_root = "";

	err = -ENOMEM;
	host_root_path = kmalloc(strlen(root_ino) + 1
				 + strlen(req_root) + 1, GFP_KERNEL);
	if (host_root_path == NULL)
		goto out;

	sprintf(host_root_path, "%s/%s", root_ino, req_root);

	root_inode = hostfs_iget(sb);
	if (IS_ERR(root_inode)) {
		err = PTR_ERR(root_inode);
		goto out_free;
	}

	err = init_inode(root_inode, NULL);
	if (err)
		goto out_put;

	HOSTFS_I(root_inode)->host_filename = host_root_path;
	/*
	 * Avoid that in the error path, iput(root_inode) frees again
	 * host_root_path through hostfs_destroy_inode!
	 */
	host_root_path = NULL;

	err = -ENOMEM;
	sb->s_root = d_alloc_root(root_inode);
	if (sb->s_root == NULL)
		goto out_put;

	err = hostfs_read_inode(root_inode);
	if (err) {
		/* No iput in this case because the dput does that for us */
		dput(sb->s_root);
		sb->s_root = NULL;
		goto out;
	}

	return 0;

out_put:
	iput(root_inode);
out_free:
	kfree(host_root_path);
out:
	return err;
}