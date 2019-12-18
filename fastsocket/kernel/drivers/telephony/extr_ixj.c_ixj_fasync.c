#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_7__ {int /*<<< orphan*/  async_queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_inode; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  NUM (int /*<<< orphan*/ ) ; 
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 TYPE_3__* get_ixj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixj_fasync(int fd, struct file *file_p, int mode)
{
	IXJ *j = get_ixj(NUM(file_p->f_path.dentry->d_inode));

	return fasync_helper(fd, file_p, mode, &j->async_queue);
}