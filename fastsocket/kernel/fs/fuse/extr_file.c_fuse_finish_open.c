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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_mapping; } ;
struct fuse_inode {int /*<<< orphan*/  write_files; } ;
struct fuse_file {int open_flags; int /*<<< orphan*/  write_entry; } ;
struct fuse_conn {int /*<<< orphan*/  lock; } ;
struct file {int f_mode; int /*<<< orphan*/ * f_op; struct fuse_file* private_data; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int FOPEN_DIRECT_IO ; 
 int FOPEN_KEEP_CACHE ; 
 int FOPEN_NONSEEKABLE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_direct_io_file_operations ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fuse_finish_open(struct inode *inode, struct file *file)
{
	struct fuse_file *ff = file->private_data;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_inode *fi = get_fuse_inode(inode);

	if (ff->open_flags & FOPEN_DIRECT_IO)
		file->f_op = &fuse_direct_io_file_operations;
	if (!(ff->open_flags & FOPEN_KEEP_CACHE))
		invalidate_inode_pages2(inode->i_mapping);
	if (ff->open_flags & FOPEN_NONSEEKABLE)
		nonseekable_open(inode, file);

 	/* file might be required for fallocate */
	spin_lock(&fc->lock);
	if (S_ISREG(inode->i_mode) && (file->f_mode & FMODE_WRITE))
		list_add(&ff->write_entry, &fi->write_files);
	spin_unlock(&fc->lock);
}