#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ e_kind; int e_class; } ;
typedef  TYPE_1__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* _libelf_ehdr (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int _libelf_setshstrndx (TYPE_1__*,void*,int,size_t) ; 

int
elf_setshstrndx(Elf *e, size_t strndx)
{
	void *eh;
	int ec;

	if (e == NULL || e->e_kind != ELF_K_ELF ||
	    ((ec = e->e_class) != ELFCLASS32 && ec != ELFCLASS64) ||
	    ((eh = _libelf_ehdr(e, ec, 0)) == NULL)) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	return (_libelf_setshstrndx(e, eh, ec, strndx));
}