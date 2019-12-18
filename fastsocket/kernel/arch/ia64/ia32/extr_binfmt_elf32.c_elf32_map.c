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
struct file {int dummy; } ;
struct elf_phdr {unsigned long p_vaddr; scalar_t__ p_offset; scalar_t__ p_filesz; } ;

/* Variables and functions */
 unsigned long IA32_PAGE_MASK ; 
 unsigned long ia32_do_mmap (struct file*,unsigned long,scalar_t__,int,int,scalar_t__) ; 

__attribute__((used)) static unsigned long
elf32_map(struct file *filep, unsigned long addr, struct elf_phdr *eppnt,
		int prot, int type, unsigned long unused)
{
	unsigned long pgoff = (eppnt->p_vaddr) & ~IA32_PAGE_MASK;

	return ia32_do_mmap(filep, (addr & IA32_PAGE_MASK), eppnt->p_filesz + pgoff, prot, type,
			    eppnt->p_offset - pgoff);
}