#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int e_class; } ;
struct TYPE_10__ {int /*<<< orphan*/  e_shstrndx; int /*<<< orphan*/  e_shnum; int /*<<< orphan*/  e_shentsize; int /*<<< orphan*/  e_phnum; int /*<<< orphan*/  e_phentsize; int /*<<< orphan*/  e_ehsize; int /*<<< orphan*/  e_flags; int /*<<< orphan*/  e_shoff; int /*<<< orphan*/  e_phoff; int /*<<< orphan*/  e_entry; int /*<<< orphan*/  e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_ident; } ;
struct TYPE_9__ {int /*<<< orphan*/  e_shstrndx; int /*<<< orphan*/  e_shnum; int /*<<< orphan*/  e_shentsize; int /*<<< orphan*/  e_phnum; int /*<<< orphan*/  e_phentsize; int /*<<< orphan*/  e_ehsize; int /*<<< orphan*/  e_flags; int /*<<< orphan*/  e_shoff; int /*<<< orphan*/  e_phoff; int /*<<< orphan*/  e_entry; int /*<<< orphan*/  e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  TYPE_1__ Elf64_Ehdr ;
typedef  TYPE_3__ Elf32_Ehdr ;
typedef  TYPE_4__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* _libelf_ehdr (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

GElf_Ehdr *
gelf_getehdr(Elf *e, GElf_Ehdr *d)
{
	int ec;
	Elf32_Ehdr *eh32;
	Elf64_Ehdr *eh64;

	if (d == NULL || e == NULL ||
	    ((ec = e->e_class) != ELFCLASS32 && ec != ELFCLASS64)) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	if (ec == ELFCLASS32) {
		if ((eh32 = _libelf_ehdr(e, ELFCLASS32, 0)) == NULL)
			return (NULL);

		(void) memcpy(d->e_ident, eh32->e_ident,
		    sizeof(eh32->e_ident));
		d->e_type		= eh32->e_type;
		d->e_machine		= eh32->e_machine;
		d->e_version		= eh32->e_version;
		d->e_entry		= eh32->e_entry;
		d->e_phoff		= eh32->e_phoff;
		d->e_shoff		= eh32->e_shoff;
		d->e_flags		= eh32->e_flags;
		d->e_ehsize		= eh32->e_ehsize;
		d->e_phentsize		= eh32->e_phentsize;
		d->e_phnum		= eh32->e_phnum;
		d->e_shentsize		= eh32->e_shentsize;
		d->e_shnum		= eh32->e_shnum;
		d->e_shstrndx		= eh32->e_shstrndx;

		return (d);
	}

	assert(ec == ELFCLASS64);

	if ((eh64 = _libelf_ehdr(e, ELFCLASS64, 0)) == NULL)
		return (NULL);
	*d = *eh64;

	return (d);
}