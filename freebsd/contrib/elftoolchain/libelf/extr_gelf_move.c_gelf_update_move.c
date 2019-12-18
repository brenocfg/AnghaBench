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
struct TYPE_19__ {int /*<<< orphan*/  m_stride; int /*<<< orphan*/  m_repeat; int /*<<< orphan*/  m_value; } ;
struct TYPE_14__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_13__ {int /*<<< orphan*/  sh_type; } ;
struct TYPE_15__ {TYPE_2__ s_shdr64; TYPE_1__ s_shdr32; } ;
struct TYPE_18__ {TYPE_3__ s_shdr; TYPE_9__* s_elf; } ;
struct TYPE_17__ {int /*<<< orphan*/  m_stride; int /*<<< orphan*/  m_repeat; int /*<<< orphan*/  m_value; } ;
typedef  TYPE_5__ GElf_Move ;
typedef  TYPE_6__ Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  TYPE_5__ Elf64_Move ;
typedef  TYPE_8__ Elf32_Move ;
typedef  TYPE_9__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_T_MOVE ; 
 int /*<<< orphan*/  LIBELF_COPY_U32 (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t _libelf_msize (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _libelf_xlate_shtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  m_info ; 
 int /*<<< orphan*/  m_poffset ; 

int
gelf_update_move(Elf_Data *ed, int ndx, GElf_Move *gm)
{
	int ec;
	Elf *e;
	size_t msz;
	Elf_Scn *scn;
	uint32_t sh_type;
	Elf32_Move *move32;
	Elf64_Move *move64;
	struct _Libelf_Data *d;

	d = (struct _Libelf_Data *) ed;

	if (d == NULL || ndx < 0 || gm == NULL ||
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

	if (_libelf_xlate_shtype(sh_type) != ELF_T_MOVE) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	msz = _libelf_msize(ELF_T_MOVE, ec, e->e_version);

	assert(msz > 0);
	assert(ndx >= 0);

	if (msz * (size_t) ndx >= d->d_data.d_size) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	if (ec == ELFCLASS32) {
		move32 = (Elf32_Move *) d->d_data.d_buf + ndx;

		move32->m_value  = gm->m_value;
		LIBELF_COPY_U32(move32, gm, m_info);
		LIBELF_COPY_U32(move32, gm, m_poffset);
		move32->m_repeat  = gm->m_repeat;
		move32->m_stride = gm->m_stride;

	} else {
		move64 = (Elf64_Move *) d->d_data.d_buf + ndx;

		*move64 = *gm;
	}

	return (1);
}