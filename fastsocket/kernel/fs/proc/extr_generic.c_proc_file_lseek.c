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
 int /*<<< orphan*/  MAX_NON_LFS ; 

__attribute__((used)) static loff_t
proc_file_lseek(struct file *file, loff_t offset, int orig)
{
	loff_t retval = -EINVAL;
	switch (orig) {
	case 1:
		offset += file->f_pos;
	/* fallthrough */
	case 0:
		if (offset < 0 || offset > MAX_NON_LFS)
			break;
		file->f_pos = retval = offset;
	}
	return retval;
}