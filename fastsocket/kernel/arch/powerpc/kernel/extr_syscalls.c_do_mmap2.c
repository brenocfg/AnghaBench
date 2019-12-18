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

/* Variables and functions */
 unsigned long EINVAL ; 
 int /*<<< orphan*/  arch_validate_prot (unsigned long) ; 
 unsigned long sys_mmap_pgoff (unsigned long,size_t,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline unsigned long do_mmap2(unsigned long addr, size_t len,
			unsigned long prot, unsigned long flags,
			unsigned long fd, unsigned long off, int shift)
{
	unsigned long ret = -EINVAL;

	if (!arch_validate_prot(prot))
		goto out;

	if (shift) {
		if (off & ((1 << shift) - 1))
			goto out;
		off >>= shift;
	}

	ret = sys_mmap_pgoff(addr, len, prot, flags, fd, off);
out:
	return ret;
}