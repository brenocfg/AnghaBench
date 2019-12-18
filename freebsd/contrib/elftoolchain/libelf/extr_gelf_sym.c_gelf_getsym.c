#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_15__ {size_t d_size; scalar_t__ d_buf; } ;
struct _Libelf_Data {TYPE_4__ d_data; TYPE_6__* d_scn; } ;
struct TYPE_19__ {int e_class; int /*<<< orphan*/  e_version; } ;
struct TYPE_18__ {int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; scalar_t__ st_size; scalar_t__ st_value; int /*<<< orphan*/  st_name; } ;
struct TYPE_13__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_12__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_14__ {TYPE_2__ s_shdr64; TYPE_1__ s_shdr32; } ;
struct TYPE_17__ {TYPE_3__ s_shdr; TYPE_9__* s_elf; } ;
struct TYPE_16__ {int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; scalar_t__ st_size; scalar_t__ st_value; int /*<<< orphan*/  st_name; } ;
typedef  TYPE_5__ GElf_Sym ;
typedef  TYPE_6__ Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  scalar_t__ Elf64_Xword ;
typedef  TYPE_5__ Elf64_Sym ;
typedef  scalar_t__ Elf64_Addr ;
typedef  TYPE_8__ Elf32_Sym ;
typedef  TYPE_9__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_T_SYM ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t _libelf_msize (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _libelf_xlate_shtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

GElf_Sym *
gelf_getsym(Elf_Data *ed, int ndx, GElf_Sym *dst)
{
	int ec;
	Elf *e;
	size_t msz;
	Elf_Scn *scn;
	uint32_t sh_type;
	Elf32_Sym *sym32;
	Elf64_Sym *sym64;
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

	if (_libelf_xlate_shtype(sh_type) != ELF_T_SYM) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	msz = _libelf_msize(ELF_T_SYM, ec, e->e_version);

	assert(msz > 0);
	assert(ndx >= 0);

	if (msz * (size_t) ndx >= d->d_data.d_size) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	if (ec == ELFCLASS32) {
		sym32 = (Elf32_Sym *) d->d_data.d_buf + ndx;

		dst->st_name  = sym32->st_name;
		dst->st_value = (Elf64_Addr) sym32->st_value;
		dst->st_size  = (Elf64_Xword) sym32->st_size;
		dst->st_info  = sym32->st_info;
		dst->st_other = sym32->st_other;
		dst->st_shndx = sym32->st_shndx;
	} else {
		sym64 = (Elf64_Sym *) d->d_data.d_buf + ndx;

		*dst = *sym64;
	}

	return (dst);
}