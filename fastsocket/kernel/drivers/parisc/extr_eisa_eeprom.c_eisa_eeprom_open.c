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
struct inode {int dummy; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  cycle_kernel_lock () ; 

__attribute__((used)) static int eisa_eeprom_open(struct inode *inode, struct file *file)
{
	cycle_kernel_lock();

	if (file->f_mode & FMODE_WRITE)
		return -EINVAL;
   
	return 0;
}