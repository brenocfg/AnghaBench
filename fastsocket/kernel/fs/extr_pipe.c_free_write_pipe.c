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
struct file {int /*<<< orphan*/  f_path; TYPE_1__* f_dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pipe_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_filp (struct file*) ; 

void free_write_pipe(struct file *f)
{
	free_pipe_info(f->f_dentry->d_inode);
	path_put(&f->f_path);
	put_filp(f);
}