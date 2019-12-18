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
struct qstr {int len; char* name; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {int /*<<< orphan*/  private_data; TYPE_1__ f_path; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  d_alloc (int /*<<< orphan*/ ,struct qstr*) ; 

int dcache_dir_open(struct inode *inode, struct file *file)
{
	static struct qstr cursor_name = {.len = 1, .name = "."};

	file->private_data = d_alloc(file->f_path.dentry, &cursor_name);

	return file->private_data ? 0 : -ENOMEM;
}