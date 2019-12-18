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
struct inode {int dummy; } ;
struct iattr {int /*<<< orphan*/  ia_valid; struct file* ia_file; int /*<<< orphan*/  ia_size; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_FILE ; 
 int /*<<< orphan*/  ATTR_SIZE ; 
 int /*<<< orphan*/  fuse_do_setattr (struct inode*,struct iattr*,struct file*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 

__attribute__((used)) static void fuse_do_truncate(struct file *file)
{
	struct inode *inode = file->f_mapping->host;
	struct iattr attr;

	attr.ia_valid = ATTR_SIZE;
	attr.ia_size = i_size_read(inode);

	attr.ia_file = file;
	attr.ia_valid |= ATTR_FILE;

	fuse_do_setattr(inode, &attr, file);
}