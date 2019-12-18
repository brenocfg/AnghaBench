#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int /*<<< orphan*/  PF_SUPERPRIV ; 
 int /*<<< orphan*/  SECURITY_CAP_AUDIT ; 
 int cap_capable (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  current_cred () ; 
 unsigned long dac_mmap_min_addr ; 

int cap_file_mmap(struct file *file, unsigned long reqprot,
		  unsigned long prot, unsigned long flags,
		  unsigned long addr, unsigned long addr_only)
{
	int ret = 0;

	if (addr < dac_mmap_min_addr) {
		ret = cap_capable(current, current_cred(), CAP_SYS_RAWIO,
				  SECURITY_CAP_AUDIT);
		/* set PF_SUPERPRIV if it turns out we allow the low mmap */
		if (ret == 0)
			current->flags |= PF_SUPERPRIV;
	}
	return ret;
}