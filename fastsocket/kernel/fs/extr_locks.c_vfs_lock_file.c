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
struct file_lock {int dummy; } ;
struct file {TYPE_1__* f_op; } ;
struct TYPE_2__ {int (* lock ) (struct file*,unsigned int,struct file_lock*) ;} ;

/* Variables and functions */
 int posix_lock_file (struct file*,struct file_lock*,struct file_lock*) ; 
 int stub1 (struct file*,unsigned int,struct file_lock*) ; 

int vfs_lock_file(struct file *filp, unsigned int cmd, struct file_lock *fl, struct file_lock *conf)
{
	if (filp->f_op && filp->f_op->lock)
		return filp->f_op->lock(filp, cmd, fl);
	else
		return posix_lock_file(filp, fl, conf);
}