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
struct vm_area_struct {int vm_flags; } ;
struct mtd_info {scalar_t__ type; } ;
struct mtd_file_info {struct mtd_info* mtd; } ;
struct file {struct mtd_file_info* private_data; } ;

/* Variables and functions */
 int ENOSYS ; 
 scalar_t__ MTD_RAM ; 
 scalar_t__ MTD_ROM ; 
 int VM_SHARED ; 

__attribute__((used)) static int mtd_mmap(struct file *file, struct vm_area_struct *vma)
{
#ifdef CONFIG_MMU
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;

	if (mtd->type == MTD_RAM || mtd->type == MTD_ROM)
		return 0;
	return -ENOSYS;
#else
	return vma->vm_flags & VM_SHARED ? 0 : -ENOSYS;
#endif
}