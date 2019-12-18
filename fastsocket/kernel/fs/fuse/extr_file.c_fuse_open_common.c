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
struct inode {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int fuse_do_open (struct fuse_conn*,int /*<<< orphan*/ ,struct file*,int) ; 
 int /*<<< orphan*/  fuse_finish_open (struct inode*,struct file*) ; 
 int generic_file_open (struct inode*,struct file*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 

int fuse_open_common(struct inode *inode, struct file *file, bool isdir)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	int err;

	err = generic_file_open(inode, file);
	if (err)
		return err;

	err = fuse_do_open(fc, get_node_id(inode), file, isdir);
	if (err)
		return err;

	fuse_finish_open(inode, file);

	return 0;
}