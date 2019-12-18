#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct file {TYPE_1__* f_op; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {TYPE_2__* mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 unsigned long EINVAL ; 
 unsigned long ENODEV ; 
 unsigned long ENOMEM ; 
 unsigned long IA32_PAGE_ALIGN (unsigned long) ; 
 unsigned long IA32_PAGE_OFFSET ; 
 int MAP_FIXED ; 
 int MAP_HUGETLB ; 
 scalar_t__ OFFSET4K (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 unsigned long do_mmap (struct file*,unsigned long,unsigned long,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 unsigned long emulate_mmap (struct file*,unsigned long,unsigned long,int,int,int /*<<< orphan*/ ) ; 
 int get_prot32 (int) ; 
 int /*<<< orphan*/  ia32_mmap_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

unsigned long
ia32_do_mmap (struct file *file, unsigned long addr, unsigned long len, int prot, int flags,
	      loff_t offset)
{
	DBG("ia32_do_mmap(file=%p,addr=0x%lx,len=0x%lx,prot=%x,flags=%x,offset=0x%llx)\n",
	    file, addr, len, prot, flags, offset);

	if (file && (!file->f_op || !file->f_op->mmap))
		return -ENODEV;

	len = IA32_PAGE_ALIGN(len);
	if (len == 0)
		return addr;

	if (len > IA32_PAGE_OFFSET || addr > IA32_PAGE_OFFSET - len)
	{
		if (flags & MAP_FIXED)
			return -ENOMEM;
		else
		return -EINVAL;
	}

	if (OFFSET4K(offset))
		return -EINVAL;

	prot = get_prot32(prot);

	if (flags & MAP_HUGETLB)
		return -ENOMEM;

#if PAGE_SHIFT > IA32_PAGE_SHIFT
	mutex_lock(&ia32_mmap_mutex);
	{
		addr = emulate_mmap(file, addr, len, prot, flags, offset);
	}
	mutex_unlock(&ia32_mmap_mutex);
#else
	down_write(&current->mm->mmap_sem);
	{
		addr = do_mmap(file, addr, len, prot, flags, offset);
	}
	up_write(&current->mm->mmap_sem);
#endif
	DBG("ia32_do_mmap: returning 0x%lx\n", addr);
	return addr;
}