#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* dbg_iface; } ;
struct TYPE_6__ {scalar_t__ eo_seccnt; struct TYPE_6__* eo_shdr; struct TYPE_6__* eo_data; struct TYPE_6__* ed_alloc; struct TYPE_6__* object; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_1__ Dwarf_Obj_Access_Interface ;
typedef  TYPE_1__ Dwarf_Elf_Object ;
typedef  TYPE_3__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
_dwarf_elf_deinit(Dwarf_Debug dbg)
{
	Dwarf_Obj_Access_Interface *iface;
	Dwarf_Elf_Object *e;
	int i;

	iface = dbg->dbg_iface;
	assert(iface != NULL);

	e = iface->object;
	assert(e != NULL);

	if (e->eo_data) {
		for (i = 0; (Dwarf_Unsigned) i < e->eo_seccnt; i++) {
			if (e->eo_data[i].ed_alloc)
				free(e->eo_data[i].ed_alloc);
		}
		free(e->eo_data);
	}
	if (e->eo_shdr)
		free(e->eo_shdr);

	free(e);
	free(iface);

	dbg->dbg_iface = NULL;
}