#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* u; int /*<<< orphan*/  at_form; int /*<<< orphan*/  at_attrib; TYPE_2__* at_die; } ;
struct TYPE_12__ {int /*<<< orphan*/  die_attr; int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_11__ {int /*<<< orphan*/  s64; } ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  TYPE_2__* Dwarf_P_Die ;
typedef  TYPE_3__* Dwarf_P_Attribute ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_3__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_AT_const_value ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 scalar_t__ DW_DLE_NONE ; 
 TYPE_3__* DW_DLV_BADADDR ; 
 int /*<<< orphan*/  DW_FORM_sdata ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _dwarf_attr_alloc (TYPE_2__*,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  at_next ; 

Dwarf_P_Attribute
dwarf_add_AT_const_value_signedint(Dwarf_P_Die die, Dwarf_Signed value,
    Dwarf_Error *error)
{
	Dwarf_Attribute at;
	Dwarf_Debug dbg;

	dbg = die != NULL ? die->die_dbg : NULL;

	if (die == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_BADADDR);
	}

	if (_dwarf_attr_alloc(die, &at, error) != DW_DLE_NONE)
		return (DW_DLV_BADADDR);

	at->at_die = die;
	at->at_attrib = DW_AT_const_value;
	at->at_form = DW_FORM_sdata;
	at->u[0].s64 = value;

	STAILQ_INSERT_TAIL(&die->die_attr, at, at_next);

	return (at);
}