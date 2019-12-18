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
 scalar_t__ MBCS_SRAM_SIZE ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 

__attribute__((used)) static loff_t mbcs_sram_llseek(struct file * filp, loff_t off, int whence)
{
	loff_t newpos;

	switch (whence) {
	case SEEK_SET:
		newpos = off;
		break;

	case SEEK_CUR:
		newpos = filp->f_pos + off;
		break;

	case SEEK_END:
		newpos = MBCS_SRAM_SIZE + off;
		break;

	default:		/* can't happen */
		return -EINVAL;
	}

	if (newpos < 0)
		return -EINVAL;

	filp->f_pos = newpos;

	return newpos;
}