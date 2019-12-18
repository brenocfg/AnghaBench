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
struct file {int f_pos; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SEEK_CUR 129 
#define  SEEK_SET 128 

__attribute__((used)) static loff_t dev_mem_seek(struct file *file, loff_t offset, int orig)
{
	loff_t ret;

	/* only requests of dword-aligned size and offset are supported */
	if (offset % 4)
		return -EINVAL;

	switch (orig) {
	case SEEK_SET:
		file->f_pos = offset;
		ret = file->f_pos;
		break;
	case SEEK_CUR:
		file->f_pos += offset;
		ret = file->f_pos;
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}