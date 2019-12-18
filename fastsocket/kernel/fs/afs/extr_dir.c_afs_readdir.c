#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {unsigned int f_pos; int /*<<< orphan*/ * private_data; TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  filldir_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_4__ {TYPE_3__* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int afs_dir_iterate (TYPE_3__*,unsigned int*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_readdir(struct file *file, void *cookie, filldir_t filldir)
{
	unsigned fpos;
	int ret;

	_enter("{%Ld,{%lu}}",
	       file->f_pos, file->f_path.dentry->d_inode->i_ino);

	ASSERT(file->private_data != NULL);

	fpos = file->f_pos;
	ret = afs_dir_iterate(file->f_path.dentry->d_inode, &fpos,
			      cookie, filldir, file->private_data);
	file->f_pos = fpos;

	_leave(" = %d", ret);
	return ret;
}