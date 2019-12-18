#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* at_refdie; int /*<<< orphan*/  at_form; int /*<<< orphan*/  at_attrib; TYPE_1__* at_die; } ;
struct TYPE_15__ {int dbg_offset_size; } ;
struct TYPE_14__ {int /*<<< orphan*/  die_attr; } ;
typedef  TYPE_1__* Dwarf_P_Die ;
typedef  TYPE_2__* Dwarf_P_Debug ;
typedef  TYPE_3__* Dwarf_P_Attribute ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_3__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 scalar_t__ DW_DLE_NONE ; 
 TYPE_3__* DW_DLV_BADADDR ; 
 int /*<<< orphan*/  DW_FORM_ref4 ; 
 int /*<<< orphan*/  DW_FORM_ref8 ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _dwarf_attr_alloc (TYPE_1__*,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  at_next ; 

Dwarf_P_Attribute
dwarf_add_AT_reference(Dwarf_P_Debug dbg, Dwarf_P_Die die, Dwarf_Half attr,
    Dwarf_P_Die ref_die, Dwarf_Error *error)
{
	Dwarf_Attribute at;

	if (dbg == NULL || die == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_BADADDR);
	}

	if (_dwarf_attr_alloc(die, &at, error) != DW_DLE_NONE)
		return (DW_DLV_BADADDR);

	at->at_die = die;
	at->at_attrib = attr;
	if (dbg->dbg_offset_size == 4)
		at->at_form = DW_FORM_ref4;
	else
		at->at_form = DW_FORM_ref8;

	at->at_refdie = ref_die;

	STAILQ_INSERT_TAIL(&die->die_attr, at, at_next);

	return (at);
}