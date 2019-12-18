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
typedef  int /*<<< orphan*/  u32 ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned long CONFIG_LSM_MMAP_MIN_ADDR ; 
 unsigned long MAP_SHARED ; 
 unsigned long MAP_TYPE ; 
 int /*<<< orphan*/  MEMPROTECT__MMAP_ZERO ; 
 int /*<<< orphan*/  SECCLASS_MEMPROTECT ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cap_file_mmap (struct file*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  current_sid () ; 
 int file_map_prot_check (struct file*,unsigned long,int) ; 
 scalar_t__ selinux_checkreqprot ; 

__attribute__((used)) static int selinux_file_mmap(struct file *file, unsigned long reqprot,
			     unsigned long prot, unsigned long flags,
			     unsigned long addr, unsigned long addr_only)
{
	int rc = 0;
	u32 sid = current_sid();

	/*
	 * notice that we are intentionally putting the SELinux check before
	 * the secondary cap_file_mmap check.  This is such a likely attempt
	 * at bad behaviour/exploit that we always want to get the AVC, even
	 * if DAC would have also denied the operation.
	 */
	if (addr < CONFIG_LSM_MMAP_MIN_ADDR) {
		rc = avc_has_perm(sid, sid, SECCLASS_MEMPROTECT,
				  MEMPROTECT__MMAP_ZERO, NULL);
		if (rc)
			return rc;
	}

	/* do DAC check on address space usage */
	rc = cap_file_mmap(file, reqprot, prot, flags, addr, addr_only);
	if (rc || addr_only)
		return rc;

	if (selinux_checkreqprot)
		prot = reqprot;

	return file_map_prot_check(file, prot,
				   (flags & MAP_TYPE) == MAP_SHARED);
}