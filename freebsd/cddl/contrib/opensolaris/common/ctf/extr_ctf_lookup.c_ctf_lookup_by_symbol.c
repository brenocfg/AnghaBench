#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort_t ;
typedef  scalar_t__ ulong_t ;
struct TYPE_7__ {int cts_entsize; int /*<<< orphan*/ * cts_data; } ;
typedef  TYPE_1__ ctf_sect_t ;
typedef  scalar_t__ ctf_id_t ;
struct TYPE_8__ {scalar_t__ ctf_nsyms; unsigned int* ctf_sxlate; scalar_t__ ctf_buf; TYPE_1__ ctf_symtab; } ;
typedef  TYPE_2__ ctf_file_t ;
struct TYPE_10__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  st_info; } ;
typedef  TYPE_3__ Elf64_Sym ;
typedef  TYPE_4__ Elf32_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  ECTF_NOSYMTAB ; 
 int /*<<< orphan*/  ECTF_NOTDATA ; 
 int /*<<< orphan*/  ECTF_NOTYPEDAT ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ ELF32_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF64_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STT_OBJECT ; 
 scalar_t__ ctf_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 

ctf_id_t
ctf_lookup_by_symbol(ctf_file_t *fp, ulong_t symidx)
{
	const ctf_sect_t *sp = &fp->ctf_symtab;
	ctf_id_t type;

	if (sp->cts_data == NULL)
		return (ctf_set_errno(fp, ECTF_NOSYMTAB));

	if (symidx >= fp->ctf_nsyms)
		return (ctf_set_errno(fp, EINVAL));

	if (sp->cts_entsize == sizeof (Elf32_Sym)) {
		const Elf32_Sym *symp = (Elf32_Sym *)sp->cts_data + symidx;
		if (ELF32_ST_TYPE(symp->st_info) != STT_OBJECT)
			return (ctf_set_errno(fp, ECTF_NOTDATA));
	} else {
		const Elf64_Sym *symp = (Elf64_Sym *)sp->cts_data + symidx;
		if (ELF64_ST_TYPE(symp->st_info) != STT_OBJECT)
			return (ctf_set_errno(fp, ECTF_NOTDATA));
	}

	if (fp->ctf_sxlate[symidx] == -1u)
		return (ctf_set_errno(fp, ECTF_NOTYPEDAT));

	type = *(ushort_t *)((uintptr_t)fp->ctf_buf + fp->ctf_sxlate[symidx]);
	if (type == 0)
		return (ctf_set_errno(fp, ECTF_NOTYPEDAT));

	return (type);
}