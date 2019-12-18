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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_RELEASE ; 
 int /*<<< orphan*/  fuse_release_common (struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_release(struct inode *inode, struct file *file)
{
	fuse_release_common(file, FUSE_RELEASE);

	/* return value is ignored by VFS */
	return 0;
}