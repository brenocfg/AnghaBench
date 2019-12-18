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
struct file {scalar_t__ f_pos; struct ctrl_dbg* private_data; } ;
struct ctrl_dbg {scalar_t__ size; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static loff_t lseek(struct file *file, loff_t off, int whence)
{
	struct ctrl_dbg *dbg;
	loff_t new = -1;

	lock_kernel();
	dbg = file->private_data;

	switch (whence) {
	case 0:
		new = off;
		break;
	case 1:
		new = file->f_pos + off;
		break;
	}
	if (new < 0 || new > dbg->size) {
		unlock_kernel();
		return -EINVAL;
	}
	unlock_kernel();
	return (file->f_pos = new);
}