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
struct kiocb {struct file* ki_filp; } ;
struct file {TYPE_1__* f_op; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* aio_fsync ) (struct kiocb*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  stub1 (struct kiocb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t aio_fsync(struct kiocb *iocb)
{
	struct file *file = iocb->ki_filp;
	ssize_t ret = -EINVAL;

	if (file->f_op->aio_fsync)
		ret = file->f_op->aio_fsync(iocb, 0);
	return ret;
}