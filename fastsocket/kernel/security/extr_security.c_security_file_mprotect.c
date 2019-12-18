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
struct vm_area_struct {int dummy; } ;
struct TYPE_2__ {int (* file_mprotect ) (struct vm_area_struct*,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct vm_area_struct*,unsigned long,unsigned long) ; 

int security_file_mprotect(struct vm_area_struct *vma, unsigned long reqprot,
			    unsigned long prot)
{
	return security_ops->file_mprotect(vma, reqprot, prot);
}