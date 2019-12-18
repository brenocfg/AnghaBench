#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {int d_align; int /*<<< orphan*/  d_version; int /*<<< orphan*/  d_type; scalar_t__ d_size; scalar_t__ d_off; int /*<<< orphan*/ * d_buf; } ;
struct _Libelf_Data {TYPE_2__ d_data; } ;
struct TYPE_11__ {scalar_t__ e_kind; scalar_t__ e_rawfile; } ;
struct TYPE_9__ {scalar_t__ s_size; int /*<<< orphan*/  s_data; TYPE_3__* s_elf; } ;
typedef  TYPE_1__ Elf_Scn ;
typedef  TYPE_2__ Elf_Data ;
typedef  TYPE_3__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int /*<<< orphan*/  ELF_C_SET ; 
 int /*<<< orphan*/  ELF_F_DIRTY ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  ELF_T_BYTE ; 
 int /*<<< orphan*/  LIBELF_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct _Libelf_Data*,int /*<<< orphan*/ ) ; 
 struct _Libelf_Data* _libelf_allocate_data (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  d_next ; 
 int /*<<< orphan*/  elf_flagscn (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * elf_getdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  version ; 

Elf_Data *
elf_newdata(Elf_Scn *s)
{
	Elf *e;
	struct _Libelf_Data *d;

	if (s == NULL || (e = s->s_elf) == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	assert(e->e_kind == ELF_K_ELF);

	/*
	 * elf_newdata() has to append a data descriptor, so
	 * bring in existing section data if not already present.
	 */
	if (e->e_rawfile && s->s_size > 0 && STAILQ_EMPTY(&s->s_data))
		if (elf_getdata(s, NULL) == NULL)
			return (NULL);

	if ((d = _libelf_allocate_data(s)) == NULL)
		return (NULL);

	STAILQ_INSERT_TAIL(&s->s_data, d, d_next);

	d->d_data.d_align = 1;
	d->d_data.d_buf = NULL;
	d->d_data.d_off = (uint64_t) ~0;
	d->d_data.d_size = 0;
	d->d_data.d_type = ELF_T_BYTE;
	d->d_data.d_version = LIBELF_PRIVATE(version);

	(void) elf_flagscn(s, ELF_C_SET, ELF_F_DIRTY);

	return (&d->d_data);
}