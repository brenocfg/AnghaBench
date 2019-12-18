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
struct file {int f_mode; TYPE_1__* f_op; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* llseek ) (struct file*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int FMODE_LSEEK ; 
 int /*<<< orphan*/  default_llseek (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  no_llseek (struct file*,int /*<<< orphan*/ ,int) ; 

loff_t vfs_llseek(struct file *file, loff_t offset, int origin)
{
	loff_t (*fn)(struct file *, loff_t, int);

	fn = no_llseek;
	if (file->f_mode & FMODE_LSEEK) {
		fn = default_llseek;
		if (file->f_op && file->f_op->llseek)
			fn = file->f_op->llseek;
	}
	return fn(file, offset, origin);
}