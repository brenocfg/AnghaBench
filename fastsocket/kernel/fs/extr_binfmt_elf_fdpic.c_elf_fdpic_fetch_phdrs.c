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
struct elf_phdr {int dummy; } ;
struct TYPE_2__ {int e_phentsize; unsigned int e_phnum; int /*<<< orphan*/  e_phoff; } ;
struct elf_fdpic_params {int /*<<< orphan*/  stack_size; int /*<<< orphan*/  flags; TYPE_1__ hdr; struct elf32_phdr* phdrs; } ;
struct elf32_phdr {scalar_t__ p_type; int p_flags; int /*<<< orphan*/  p_memsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_FDPIC_FLAG_EXEC_STACK ; 
 int /*<<< orphan*/  ELF_FDPIC_FLAG_NOEXEC_STACK ; 
 int ENOEXEC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PF_X ; 
 scalar_t__ PT_GNU_STACK ; 
 int kernel_read (struct file*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 struct elf32_phdr* kmalloc (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int elf_fdpic_fetch_phdrs(struct elf_fdpic_params *params,
				 struct file *file)
{
	struct elf32_phdr *phdr;
	unsigned long size;
	int retval, loop;

	if (params->hdr.e_phentsize != sizeof(struct elf_phdr))
		return -ENOMEM;
	if (params->hdr.e_phnum > 65536U / sizeof(struct elf_phdr))
		return -ENOMEM;

	size = params->hdr.e_phnum * sizeof(struct elf_phdr);
	params->phdrs = kmalloc(size, GFP_KERNEL);
	if (!params->phdrs)
		return -ENOMEM;

	retval = kernel_read(file, params->hdr.e_phoff,
			     (char *) params->phdrs, size);
	if (unlikely(retval != size))
		return retval < 0 ? retval : -ENOEXEC;

	/* determine stack size for this binary */
	phdr = params->phdrs;
	for (loop = 0; loop < params->hdr.e_phnum; loop++, phdr++) {
		if (phdr->p_type != PT_GNU_STACK)
			continue;

		if (phdr->p_flags & PF_X)
			params->flags |= ELF_FDPIC_FLAG_EXEC_STACK;
		else
			params->flags |= ELF_FDPIC_FLAG_NOEXEC_STACK;

		params->stack_size = phdr->p_memsz;
		break;
	}

	return 0;
}