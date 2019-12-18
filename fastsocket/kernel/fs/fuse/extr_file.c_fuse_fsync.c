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
struct file {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int fuse_fsync_common (struct file*,struct dentry*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_fsync(struct file *file, struct dentry *de, int datasync)
{
	return fuse_fsync_common(file, de, datasync, 0);
}