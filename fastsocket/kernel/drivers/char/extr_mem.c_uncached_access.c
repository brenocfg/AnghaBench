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
struct file {int f_flags; } ;

/* Variables and functions */
 int EFI_MEMORY_WB ; 
 int O_SYNC ; 
 unsigned long __pa (int /*<<< orphan*/ ) ; 
 int efi_mem_attributes (unsigned long) ; 
 int /*<<< orphan*/  high_memory ; 

__attribute__((used)) static inline int uncached_access(struct file *file, unsigned long addr)
{
#if defined(CONFIG_IA64)
	/*
	 * On ia64, we ignore O_SYNC because we cannot tolerate memory attribute aliases.
	 */
	return !(efi_mem_attributes(addr) & EFI_MEMORY_WB);
#elif defined(CONFIG_MIPS)
	{
		extern int __uncached_access(struct file *file,
					     unsigned long addr);

		return __uncached_access(file, addr);
	}
#else
	/*
	 * Accessing memory above the top the kernel knows about or through a file pointer
	 * that was marked O_SYNC will be done non-cached.
	 */
	if (file->f_flags & O_SYNC)
		return 1;
	return addr >= __pa(high_memory);
#endif
}