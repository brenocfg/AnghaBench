#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file {int /*<<< orphan*/  f_pos; TYPE_3__* f_op; } ;
typedef  int ssize_t ;
typedef  int loff_t ;
struct TYPE_8__ {TYPE_2__* signal; } ;
struct TYPE_7__ {int (* write ) (struct file*,void const*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__* rlim; } ;
struct TYPE_5__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 int EIO ; 
 size_t RLIMIT_CORE ; 
 TYPE_4__* current ; 
 int stub1 (struct file*,void const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spufs_dump_write(struct file *file, const void *addr, int nr, loff_t *foffset)
{
	unsigned long limit = current->signal->rlim[RLIMIT_CORE].rlim_cur;
	ssize_t written;

	if (*foffset + nr > limit)
		return -EIO;

	written = file->f_op->write(file, addr, nr, &file->f_pos);
	*foffset += written;

	if (written != nr)
		return -EIO;

	return 0;
}