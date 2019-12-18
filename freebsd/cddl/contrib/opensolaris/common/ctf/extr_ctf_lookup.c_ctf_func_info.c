#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort_t ;
typedef  scalar_t__ ulong_t ;
struct TYPE_11__ {int cts_entsize; int /*<<< orphan*/ * cts_data; } ;
typedef  TYPE_1__ ctf_sect_t ;
struct TYPE_12__ {scalar_t__ ctc_argc; int /*<<< orphan*/  ctc_flags; int /*<<< orphan*/  ctc_return; } ;
typedef  TYPE_2__ ctf_funcinfo_t ;
struct TYPE_13__ {scalar_t__ ctf_nsyms; unsigned int* ctf_sxlate; scalar_t__ ctf_buf; TYPE_1__ ctf_symtab; } ;
typedef  TYPE_3__ ctf_file_t ;
struct TYPE_15__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_14__ {int /*<<< orphan*/  st_info; } ;
typedef  TYPE_4__ Elf64_Sym ;
typedef  TYPE_5__ Elf32_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_FUNC_VARARG ; 
 scalar_t__ CTF_K_FUNCTION ; 
 scalar_t__ CTF_K_UNKNOWN ; 
 int /*<<< orphan*/  ECTF_CORRUPT ; 
 int /*<<< orphan*/  ECTF_NOFUNCDAT ; 
 int /*<<< orphan*/  ECTF_NOSYMTAB ; 
 int /*<<< orphan*/  ECTF_NOTFUNC ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ ELF32_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF64_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ LCTF_INFO_KIND (TYPE_3__*,scalar_t__) ; 
 scalar_t__ LCTF_INFO_VLEN (TYPE_3__*,scalar_t__) ; 
 scalar_t__ STT_FUNC ; 
 int ctf_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
ctf_func_info(ctf_file_t *fp, ulong_t symidx, ctf_funcinfo_t *fip)
{
	const ctf_sect_t *sp = &fp->ctf_symtab;
	const ushort_t *dp;
	ushort_t info, kind, n;

	if (sp->cts_data == NULL)
		return (ctf_set_errno(fp, ECTF_NOSYMTAB));

	if (symidx >= fp->ctf_nsyms)
		return (ctf_set_errno(fp, EINVAL));

	if (sp->cts_entsize == sizeof (Elf32_Sym)) {
		const Elf32_Sym *symp = (Elf32_Sym *)sp->cts_data + symidx;
		if (ELF32_ST_TYPE(symp->st_info) != STT_FUNC)
			return (ctf_set_errno(fp, ECTF_NOTFUNC));
	} else {
		const Elf64_Sym *symp = (Elf64_Sym *)sp->cts_data + symidx;
		if (ELF64_ST_TYPE(symp->st_info) != STT_FUNC)
			return (ctf_set_errno(fp, ECTF_NOTFUNC));
	}

	if (fp->ctf_sxlate[symidx] == -1u)
		return (ctf_set_errno(fp, ECTF_NOFUNCDAT));

	dp = (ushort_t *)((uintptr_t)fp->ctf_buf + fp->ctf_sxlate[symidx]);

	info = *dp++;
	kind = LCTF_INFO_KIND(fp, info);
	n = LCTF_INFO_VLEN(fp, info);

	if (kind == CTF_K_UNKNOWN && n == 0)
		return (ctf_set_errno(fp, ECTF_NOFUNCDAT));

	if (kind != CTF_K_FUNCTION)
		return (ctf_set_errno(fp, ECTF_CORRUPT));

	fip->ctc_return = *dp++;
	fip->ctc_argc = n;
	fip->ctc_flags = 0;

	if (n != 0 && dp[n - 1] == 0) {
		fip->ctc_flags |= CTF_FUNC_VARARG;
		fip->ctc_argc--;
	}

	return (0);
}