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
struct file {scalar_t__ f_pos; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  NVRAM_BYTES ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static loff_t nvram_llseek(struct file *file, loff_t offset, int origin)
{
	lock_kernel();
	switch (origin) {
	case 0:
		/* nothing to do */
		break;
	case 1:
		offset += file->f_pos;
		break;
	case 2:
		offset += NVRAM_BYTES;
		break;
	}
	unlock_kernel();
	return (offset >= 0) ? (file->f_pos = offset) : -EINVAL;
}