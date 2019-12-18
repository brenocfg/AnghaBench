#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {size_t d_size; scalar_t__ d_buf; } ;
struct _Libelf_Data {TYPE_4__ d_data; TYPE_5__* d_scn; } ;
struct TYPE_14__ {int /*<<< orphan*/  c_val; } ;
struct TYPE_13__ {int e_class; int /*<<< orphan*/  e_version; } ;
struct TYPE_9__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_10__ {TYPE_2__ s_shdr64; TYPE_1__ s_shdr32; } ;
struct TYPE_12__ {TYPE_3__ s_shdr; TYPE_6__* s_elf; } ;
typedef  int /*<<< orphan*/  GElf_Cap ;
typedef  TYPE_5__ Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  int /*<<< orphan*/  Elf64_Cap ;
typedef  int /*<<< orphan*/  Elf32_Cap ;
typedef  TYPE_6__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_T_CAP ; 
 int /*<<< orphan*/  LIBELF_COPY_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t _libelf_msize (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _libelf_xlate_shtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  c_tag ; 
 TYPE_7__ c_un ; 

int
gelf_update_cap(Elf_Data *ed, int ndx, GElf_Cap *gc)
{
	int ec;
	Elf *e;
	size_t msz;
	Elf_Scn *scn;
	Elf32_Cap *cap32;
	Elf64_Cap *cap64;
	uint32_t sh_type;
	struct _Libelf_Data *d;

	d = (struct _Libelf_Data *) ed;

	if (d == NULL || ndx < 0 || gc == NULL ||
	    (scn = d->d_scn) == NULL ||
	    (e = scn->s_elf) == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	ec = e->e_class;
	assert(ec == ELFCLASS32 || ec == ELFCLASS64);

	if (ec == ELFCLASS32)
		sh_type = scn->s_shdr.s_shdr32.sh_type;
	else
		sh_type = scn->s_shdr.s_shdr64.sh_type;

	if (_libelf_xlate_shtype(sh_type) != ELF_T_CAP) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	msz = _libelf_msize(ELF_T_CAP, ec, e->e_version);
	assert(msz > 0);

	if (msz * (size_t) ndx >= d->d_data.d_size) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	if (ec == ELFCLASS32) {
		cap32 = (Elf32_Cap *) d->d_data.d_buf + ndx;

		LIBELF_COPY_U32(cap32, gc, c_tag);
		LIBELF_COPY_U32(cap32, gc, c_un.c_val);
	} else {
		cap64 = (Elf64_Cap *) d->d_data.d_buf + ndx;

		*cap64 = *gc;
	}

	return (1);
}