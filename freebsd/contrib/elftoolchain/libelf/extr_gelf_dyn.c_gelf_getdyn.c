#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_21__ {size_t d_size; scalar_t__ d_buf; } ;
struct _Libelf_Data {TYPE_6__ d_data; TYPE_8__* d_scn; } ;
struct TYPE_17__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_16__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_18__ {TYPE_2__ s_shdr64; TYPE_1__ s_shdr32; } ;
struct TYPE_23__ {TYPE_3__ s_shdr; TYPE_11__* s_elf; } ;
struct TYPE_19__ {scalar_t__ d_val; } ;
struct TYPE_22__ {TYPE_4__ d_un; int /*<<< orphan*/  d_tag; } ;
struct TYPE_20__ {scalar_t__ d_val; } ;
struct TYPE_15__ {int e_class; int /*<<< orphan*/  e_version; } ;
struct TYPE_14__ {TYPE_5__ d_un; int /*<<< orphan*/  d_tag; } ;
typedef  TYPE_7__ GElf_Dyn ;
typedef  TYPE_8__ Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  scalar_t__ Elf64_Xword ;
typedef  TYPE_7__ Elf64_Dyn ;
typedef  TYPE_10__ Elf32_Dyn ;
typedef  TYPE_11__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_T_DYN ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t _libelf_msize (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _libelf_xlate_shtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

GElf_Dyn *
gelf_getdyn(Elf_Data *ed, int ndx, GElf_Dyn *dst)
{
	int ec;
	Elf *e;
	size_t msz;
	Elf_Scn *scn;
	Elf32_Dyn *dyn32;
	Elf64_Dyn *dyn64;
	uint32_t sh_type;
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

	if (_libelf_xlate_shtype(sh_type) != ELF_T_DYN) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	msz = _libelf_msize(ELF_T_DYN, ec, e->e_version);

	assert(msz > 0);
	assert(ndx >= 0);

	if (msz * (size_t) ndx >= d->d_data.d_size) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	if (ec == ELFCLASS32) {
		dyn32 = (Elf32_Dyn *) d->d_data.d_buf + ndx;

		dst->d_tag      = dyn32->d_tag;
		dst->d_un.d_val = (Elf64_Xword) dyn32->d_un.d_val;

	} else {

		dyn64 = (Elf64_Dyn *) d->d_data.d_buf + ndx;

		*dst = *dyn64;
	}

	return (dst);
}