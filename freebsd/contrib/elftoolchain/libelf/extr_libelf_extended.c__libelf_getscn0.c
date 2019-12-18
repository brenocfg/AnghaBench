#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  e_scn; } ;
struct TYPE_7__ {TYPE_1__ e_elf; } ;
struct TYPE_8__ {TYPE_2__ e_u; } ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_3__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/ * RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SHN_UNDEF ; 
 int /*<<< orphan*/ * _libelf_allocate_scn (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  scntree ; 

__attribute__((used)) static Elf_Scn *
_libelf_getscn0(Elf *e)
{
	Elf_Scn *s;

	if ((s = RB_MIN(scntree, &e->e_u.e_elf.e_scn)) != NULL)
		return (s);

	return (_libelf_allocate_scn(e, (size_t) SHN_UNDEF));
}