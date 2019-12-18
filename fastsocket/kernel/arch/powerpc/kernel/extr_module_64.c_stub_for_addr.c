#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ funcaddr; } ;
struct ppc64_stub_entry {TYPE_2__ opd; } ;
struct ppc64_opd_entry {scalar_t__ funcaddr; } ;
struct TYPE_6__ {size_t stubs_section; } ;
struct module {TYPE_1__ arch; } ;
struct TYPE_8__ {int sh_size; scalar_t__ sh_addr; } ;
typedef  TYPE_3__ Elf64_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  create_stub (TYPE_3__*,struct ppc64_stub_entry*,struct ppc64_opd_entry*,struct module*) ; 

__attribute__((used)) static unsigned long stub_for_addr(Elf64_Shdr *sechdrs,
				   unsigned long opdaddr,
				   struct module *me)
{
	struct ppc64_stub_entry *stubs;
	struct ppc64_opd_entry *opd = (void *)opdaddr;
	unsigned int i, num_stubs;

	num_stubs = sechdrs[me->arch.stubs_section].sh_size / sizeof(*stubs);

	/* Find this stub, or if that fails, the next avail. entry */
	stubs = (void *)sechdrs[me->arch.stubs_section].sh_addr;
	for (i = 0; stubs[i].opd.funcaddr; i++) {
		BUG_ON(i >= num_stubs);

		if (stubs[i].opd.funcaddr == opd->funcaddr)
			return (unsigned long)&stubs[i];
	}

	if (!create_stub(sechdrs, &stubs[i], opd, me))
		return 0;

	return (unsigned long)&stubs[i];
}