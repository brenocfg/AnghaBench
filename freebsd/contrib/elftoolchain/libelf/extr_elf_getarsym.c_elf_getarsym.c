#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t e_symtabsz; scalar_t__ e_rawsymtab; int /*<<< orphan*/ * e_symtab; } ;
struct TYPE_8__ {TYPE_1__ e_ar; } ;
struct TYPE_9__ {scalar_t__ e_kind; int e_flags; TYPE_2__ e_u; } ;
typedef  int /*<<< orphan*/  Elf_Arsym ;
typedef  TYPE_3__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE ; 
 int /*<<< orphan*/  ARGUMENT ; 
 scalar_t__ ELF_K_AR ; 
 int LIBELF_F_AR_VARIANT_SVR4 ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _libelf_ar_process_bsd_symtab (TYPE_3__*,size_t*) ; 
 int /*<<< orphan*/ * _libelf_ar_process_svr4_symtab (TYPE_3__*,size_t*) ; 

Elf_Arsym *
elf_getarsym(Elf *ar, size_t *ptr)
{
	size_t n;
	Elf_Arsym *symtab;

	n = 0;
	symtab = NULL;

	if (ar == NULL || ar->e_kind != ELF_K_AR)
		LIBELF_SET_ERROR(ARGUMENT, 0);
	else if ((symtab = ar->e_u.e_ar.e_symtab) != NULL)
		n = ar->e_u.e_ar.e_symtabsz;
	else if (ar->e_u.e_ar.e_rawsymtab)
		symtab = (ar->e_flags & LIBELF_F_AR_VARIANT_SVR4) ?
		    _libelf_ar_process_svr4_symtab(ar, &n) :
		    _libelf_ar_process_bsd_symtab(ar, &n);
	else
		LIBELF_SET_ERROR(ARCHIVE, 0);

	if (ptr)
		*ptr = n;
	return (symtab);
}