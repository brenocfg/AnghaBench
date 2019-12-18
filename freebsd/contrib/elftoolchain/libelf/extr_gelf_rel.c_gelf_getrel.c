#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_16__ {size_t d_size; scalar_t__ d_buf; } ;
struct _Libelf_Data {TYPE_4__ d_data; TYPE_6__* d_scn; } ;
struct TYPE_20__ {int e_class; int /*<<< orphan*/  e_version; } ;
struct TYPE_19__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
struct TYPE_14__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_13__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_15__ {TYPE_2__ s_shdr64; TYPE_1__ s_shdr32; } ;
struct TYPE_18__ {TYPE_3__ s_shdr; TYPE_9__* s_elf; } ;
struct TYPE_17__ {int /*<<< orphan*/  r_info; scalar_t__ r_offset; } ;
typedef  TYPE_5__ GElf_Rel ;
typedef  TYPE_6__ Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  int /*<<< orphan*/  Elf64_Xword ;
typedef  TYPE_5__ Elf64_Rel ;
typedef  scalar_t__ Elf64_Addr ;
typedef  TYPE_8__ Elf32_Rel ;
typedef  TYPE_9__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 scalar_t__ ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF64_R_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_T_REL ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _libelf_is_mips64el (TYPE_9__*) ; 
 int /*<<< orphan*/  _libelf_mips64el_r_info_tom (int /*<<< orphan*/ ) ; 
 size_t _libelf_msize (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _libelf_xlate_shtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

GElf_Rel *
gelf_getrel(Elf_Data *ed, int ndx, GElf_Rel *dst)
{
	int ec;
	Elf *e;
	size_t msz;
	Elf_Scn *scn;
	uint32_t sh_type;
	Elf32_Rel *rel32;
	Elf64_Rel *rel64;
	struct _Libelf_Data *d;

	d = (struct _Libelf_Data *) ed;

	if (d == NULL || ndx < 0 || dst == NULL ||
	    (scn = d->d_scn) == NULL ||
	    (e = scn->s_elf) == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	ec = e->e_class;
	assert(ec == ELFCLASS32 || ec == ELFCLASS64);

	if (ec == ELFCLASS32)
		sh_type = scn->s_shdr.s_shdr32.sh_type;
	else
		sh_type = scn->s_shdr.s_shdr64.sh_type;

	if (_libelf_xlate_shtype(sh_type) != ELF_T_REL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	msz = _libelf_msize(ELF_T_REL, ec, e->e_version);

	assert(msz > 0);
	assert(ndx >= 0);

	if (msz * (size_t) ndx >= d->d_data.d_size) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	if (ec == ELFCLASS32) {
		rel32 = (Elf32_Rel *) d->d_data.d_buf + ndx;

		dst->r_offset = (Elf64_Addr) rel32->r_offset;
		dst->r_info   = ELF64_R_INFO(
		    (Elf64_Xword) ELF32_R_SYM(rel32->r_info),
		    ELF32_R_TYPE(rel32->r_info));

	} else {

		rel64 = (Elf64_Rel *) d->d_data.d_buf + ndx;

		*dst = *rel64;

		if (_libelf_is_mips64el(e))
			dst->r_info = _libelf_mips64el_r_info_tom(rel64->r_info);
	}

	return (dst);
}