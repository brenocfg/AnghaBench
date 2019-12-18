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
struct file {int f_flags; int f_pos; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESPIPE ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int PAGE_SIZE ; 

__attribute__((used)) static loff_t ur_llseek(struct file *file, loff_t offset, int whence)
{
	loff_t newpos;

	if ((file->f_flags & O_ACCMODE) != O_RDONLY)
		return -ESPIPE; /* seek allowed only for reader */
	if (offset % PAGE_SIZE)
		return -ESPIPE; /* only multiples of 4K allowed */
	switch (whence) {
	case 0: /* SEEK_SET */
		newpos = offset;
		break;
	case 1: /* SEEK_CUR */
		newpos = file->f_pos + offset;
		break;
	default:
		return -EINVAL;
	}
	file->f_pos = newpos;
	return newpos;
}