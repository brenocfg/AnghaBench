#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_17__ {int /*<<< orphan*/  d_version; int /*<<< orphan*/  d_type; scalar_t__ d_size; scalar_t__ d_align; scalar_t__ d_off; int /*<<< orphan*/ * d_buf; } ;
struct _Libelf_Data {TYPE_5__ d_data; } ;
struct TYPE_18__ {scalar_t__ e_kind; int e_class; scalar_t__ e_rawsize; int /*<<< orphan*/  e_version; int /*<<< orphan*/ * e_rawfile; } ;
struct TYPE_14__ {scalar_t__ sh_type; scalar_t__ sh_offset; scalar_t__ sh_size; scalar_t__ sh_addralign; } ;
struct TYPE_13__ {scalar_t__ sh_type; scalar_t__ sh_addralign; scalar_t__ sh_size; scalar_t__ sh_offset; } ;
struct TYPE_15__ {TYPE_2__ s_shdr64; TYPE_1__ s_shdr32; } ;
struct TYPE_16__ {int /*<<< orphan*/  s_rawdata; TYPE_3__ s_shdr; TYPE_6__* s_elf; } ;
struct TYPE_12__ {TYPE_5__ d_data; } ;
typedef  TYPE_4__ Elf_Scn ;
typedef  TYPE_5__ Elf_Data ;
typedef  TYPE_6__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  ELF_T_BYTE ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECTION ; 
 scalar_t__ SHT_NOBITS ; 
 scalar_t__ SHT_NULL ; 
 struct _Libelf_Data* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct _Libelf_Data*,int /*<<< orphan*/ ) ; 
 TYPE_11__* STAILQ_NEXT (struct _Libelf_Data*,int /*<<< orphan*/ ) ; 
 struct _Libelf_Data* _libelf_allocate_data (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  d_next ; 

Elf_Data *
elf_rawdata(Elf_Scn *s, Elf_Data *ed)
{
	Elf *e;
	int elf_class;
	uint32_t sh_type;
	struct _Libelf_Data *d;
	uint64_t sh_align, sh_offset, sh_size;

	if (s == NULL || (e = s->s_elf) == NULL || e->e_rawfile == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	assert(e->e_kind == ELF_K_ELF);

	d = (struct _Libelf_Data *) ed;

	if (d == NULL && (d = STAILQ_FIRST(&s->s_rawdata)) != NULL)
		return (&d->d_data);

	if (d != NULL)
		return (&STAILQ_NEXT(d, d_next)->d_data);

	elf_class = e->e_class;

	assert(elf_class == ELFCLASS32 || elf_class == ELFCLASS64);

	if (elf_class == ELFCLASS32) {
		sh_type   = s->s_shdr.s_shdr32.sh_type;
		sh_offset = (uint64_t) s->s_shdr.s_shdr32.sh_offset;
		sh_size   = (uint64_t) s->s_shdr.s_shdr32.sh_size;
		sh_align  = (uint64_t) s->s_shdr.s_shdr32.sh_addralign;
	} else {
		sh_type   = s->s_shdr.s_shdr64.sh_type;
		sh_offset = s->s_shdr.s_shdr64.sh_offset;
		sh_size   = s->s_shdr.s_shdr64.sh_size;
		sh_align  = s->s_shdr.s_shdr64.sh_addralign;
	}

	if (sh_type == SHT_NULL) {
		LIBELF_SET_ERROR(SECTION, 0);
		return (NULL);
	}

	if (sh_type != SHT_NOBITS &&
	    (sh_offset > e->e_rawsize || sh_size > e->e_rawsize - sh_offset)) {
		LIBELF_SET_ERROR(SECTION, 0);
		return (NULL);
	}

	if ((d = _libelf_allocate_data(s)) == NULL)
		return (NULL);

	d->d_data.d_buf = (sh_type == SHT_NOBITS || sh_size == 0) ? NULL :
	    e->e_rawfile + sh_offset;
	d->d_data.d_off     = 0;
	d->d_data.d_align   = sh_align;
	d->d_data.d_size    = sh_size;
	d->d_data.d_type    = ELF_T_BYTE;
	d->d_data.d_version = e->e_version;

	STAILQ_INSERT_TAIL(&s->s_rawdata, d, d_next);

	return (&d->d_data);
}