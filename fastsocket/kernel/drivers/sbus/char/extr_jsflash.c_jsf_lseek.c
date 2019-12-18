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
struct file {int /*<<< orphan*/  f_pos; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static loff_t jsf_lseek(struct file * file, loff_t offset, int orig)
{
	loff_t ret;

	lock_kernel();
	switch (orig) {
		case 0:
			file->f_pos = offset;
			ret = file->f_pos;
			break;
		case 1:
			file->f_pos += offset;
			ret = file->f_pos;
			break;
		default:
			ret = -EINVAL;
	}
	unlock_kernel();
	return ret;
}