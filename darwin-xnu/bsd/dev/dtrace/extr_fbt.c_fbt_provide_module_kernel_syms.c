#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct symtab_command {int nsyms; scalar_t__ stroff; scalar_t__ symoff; } ;
struct modctl {scalar_t__ mod_address; } ;
struct load_command {scalar_t__ cmd; scalar_t__ cmdsize; } ;
struct TYPE_10__ {int /*<<< orphan*/  segname; scalar_t__ fileoff; scalar_t__ vmaddr; } ;
typedef  TYPE_1__ kernel_segment_command_t ;
typedef  int /*<<< orphan*/  kernel_section_t ;
typedef  int /*<<< orphan*/  kernel_nlist_t ;
struct TYPE_11__ {scalar_t__ magic; unsigned int ncmds; } ;
typedef  TYPE_2__ kernel_mach_header_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ LC_SEGMENT_KERNEL ; 
 scalar_t__ LC_SYMTAB ; 
 scalar_t__ LIT_STRNEQL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MH_MAGIC_KERNEL ; 
 int /*<<< orphan*/  SEG_LINKEDIT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  fbt_provide_kernel_section (struct modctl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  fbt_sym_cmp ; 
 int /*<<< orphan*/ * firstsect (TYPE_1__*) ; 
 TYPE_1__* firstsegfromheader (TYPE_2__*) ; 
 int /*<<< orphan*/ * kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * nextsect (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* nextsegfromheader (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
fbt_provide_module_kernel_syms(struct modctl *ctl)
{
	kernel_mach_header_t *mh = (kernel_mach_header_t *)(ctl->mod_address);
	kernel_segment_command_t *seg;
	struct load_command *cmd;
	kernel_segment_command_t *linkedit = NULL;
	struct symtab_command *symtab = NULL;
	kernel_nlist_t *syms = NULL, *sorted_syms = NULL;
	const char *strings;
	unsigned int i;
	size_t symlen;

	if (mh->magic != MH_MAGIC_KERNEL)
		return;

	cmd = (struct load_command *) &mh[1];
	for (i = 0; i < mh->ncmds; i++) {
		if (cmd->cmd == LC_SEGMENT_KERNEL) {
			kernel_segment_command_t *orig_sg = (kernel_segment_command_t *) cmd;
			if (LIT_STRNEQL(orig_sg->segname, SEG_LINKEDIT))
				linkedit = orig_sg;
		} else if (cmd->cmd == LC_SYMTAB) {
			symtab = (struct symtab_command *) cmd;
		}
		if (symtab && linkedit) {
			break;
		}
		cmd = (struct load_command *) ((caddr_t) cmd + cmd->cmdsize);
	}

	if ((symtab == NULL) || (linkedit == NULL)) {
		return;
	}

	syms = (kernel_nlist_t *)(linkedit->vmaddr + symtab->symoff - linkedit->fileoff);
	strings = (const char *)(linkedit->vmaddr + symtab->stroff - linkedit->fileoff);

	/*
	 * Make a copy of the symbol table and sort it to not cross into the next function
	 * when disassembling the function
	 */
	symlen = sizeof(kernel_nlist_t) * symtab->nsyms;
	sorted_syms = kmem_alloc(symlen, KM_SLEEP);
	bcopy(syms, sorted_syms, symlen);
	qsort(sorted_syms, symtab->nsyms, sizeof(kernel_nlist_t), fbt_sym_cmp);

	for (seg = firstsegfromheader(mh); seg != NULL; seg = nextsegfromheader(mh, seg)) {
		kernel_section_t *sect = firstsect(seg);

		if (strcmp(seg->segname, "__KLD") == 0) {
			continue;
		}

		for (sect = firstsect(seg); sect != NULL; sect = nextsect(seg, sect)) {
			fbt_provide_kernel_section(ctl, sect, sorted_syms, symtab->nsyms, strings);
		}
	}

	kmem_free(sorted_syms, symlen);
}