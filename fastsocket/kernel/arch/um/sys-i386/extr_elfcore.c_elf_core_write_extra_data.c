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
struct elfhdr {int e_phnum; scalar_t__ e_phoff; } ;
struct elf_phdr {scalar_t__ p_type; size_t p_filesz; scalar_t__ p_vaddr; } ;

/* Variables and functions */
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  dump_write (struct file*,void*,size_t) ; 
 scalar_t__ vsyscall_ehdr ; 

int elf_core_write_extra_data(struct file *file, size_t *size,
			      unsigned long limit)
{
	if ( vsyscall_ehdr ) {
		const struct elfhdr *const ehdrp =
			(struct elfhdr *) vsyscall_ehdr;
		const struct elf_phdr *const phdrp =
			(const struct elf_phdr *) (vsyscall_ehdr + ehdrp->e_phoff);
		int i;

		for (i = 0; i < ehdrp->e_phnum; ++i) {
			if (phdrp[i].p_type == PT_LOAD) {
				void *addr = (void *) phdrp[i].p_vaddr;
				size_t filesz = phdrp[i].p_filesz;

				*size += filesz;
				if (*size > limit
				    || !dump_write(file, addr, filesz))
					return 0;
			}
		}
	}
	return 1;
}