#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct TYPE_2__ {int (* file_mmap ) (struct file*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 int ima_file_mmap (struct file*,unsigned long) ; 
 TYPE_1__* security_ops ; 
 int stub1 (struct file*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

int security_file_mmap(struct file *file, unsigned long reqprot,
			unsigned long prot, unsigned long flags,
			unsigned long addr, unsigned long addr_only)
{
	int ret;

	ret = security_ops->file_mmap(file, reqprot, prot, flags, addr, addr_only);
	if (ret)
		return ret;
	return ima_file_mmap(file, prot);
}