#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  e_scn; } ;
struct TYPE_10__ {TYPE_1__ e_elf; } ;
struct TYPE_12__ {TYPE_2__ e_u; } ;
struct TYPE_11__ {size_t s_ndx; int /*<<< orphan*/  s_rawdata; int /*<<< orphan*/  s_data; TYPE_4__* s_elf; } ;
typedef  TYPE_3__ Elf_Scn ;
typedef  TYPE_4__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  RESOURCE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_3__* calloc (size_t,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  scntree ; 

Elf_Scn *
_libelf_allocate_scn(Elf *e, size_t ndx)
{
	Elf_Scn *s;

	if ((s = calloc((size_t) 1, sizeof(Elf_Scn))) == NULL) {
		LIBELF_SET_ERROR(RESOURCE, errno);
		return (NULL);
	}

	s->s_elf = e;
	s->s_ndx = ndx;

	STAILQ_INIT(&s->s_data);
	STAILQ_INIT(&s->s_rawdata);

	RB_INSERT(scntree, &e->e_u.e_elf.e_scn, s);

	return (s);
}