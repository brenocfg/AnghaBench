#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ppc64_stub_entry {int dummy; } ;
struct TYPE_6__ {unsigned int e_shnum; } ;
struct TYPE_5__ {scalar_t__ sh_type; int sh_size; scalar_t__ sh_addr; } ;
typedef  TYPE_1__ Elf64_Shdr ;
typedef  int /*<<< orphan*/  Elf64_Rela ;
typedef  TYPE_2__ Elf64_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (char*,unsigned long,...) ; 
 scalar_t__ SHT_RELA ; 
 scalar_t__ count_relocs (void*,int) ; 
 int /*<<< orphan*/  relacmp ; 
 int /*<<< orphan*/  relaswap ; 
 int /*<<< orphan*/  sort (void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long get_stubs_size(const Elf64_Ehdr *hdr,
				    const Elf64_Shdr *sechdrs)
{
	/* One extra reloc so it's always 0-funcaddr terminated */
	unsigned long relocs = 1;
	unsigned i;

	/* Every relocated section... */
	for (i = 1; i < hdr->e_shnum; i++) {
		if (sechdrs[i].sh_type == SHT_RELA) {
			DEBUGP("Found relocations in section %u\n", i);
			DEBUGP("Ptr: %p.  Number: %lu\n",
			       (void *)sechdrs[i].sh_addr,
			       sechdrs[i].sh_size / sizeof(Elf64_Rela));

			/* Sort the relocation information based on a symbol and
			 * addend key. This is a stable O(n*log n) complexity
			 * alogrithm but it will reduce the complexity of
			 * count_relocs() to linear complexity O(n)
			 */
			sort((void *)sechdrs[i].sh_addr,
			     sechdrs[i].sh_size / sizeof(Elf64_Rela),
			     sizeof(Elf64_Rela), relacmp, relaswap);

			relocs += count_relocs((void *)sechdrs[i].sh_addr,
					       sechdrs[i].sh_size
					       / sizeof(Elf64_Rela));
		}
	}

#ifdef CONFIG_DYNAMIC_FTRACE
	/* make the trampoline to the ftrace_caller */
	relocs++;
#endif

	DEBUGP("Looks like a total of %lu stubs, max\n", relocs);
	return relocs * sizeof(struct ppc64_stub_entry);
}