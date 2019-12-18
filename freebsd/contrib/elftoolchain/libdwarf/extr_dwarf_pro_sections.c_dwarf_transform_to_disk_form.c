#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dbgp_seccnt; } ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 scalar_t__ DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_DLV_NOCOUNT ; 
 scalar_t__ _dwarf_generate_sections (TYPE_1__*,int /*<<< orphan*/ *) ; 

Dwarf_Signed
dwarf_transform_to_disk_form(Dwarf_P_Debug dbg, Dwarf_Error *error)
{

	if (dbg == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_NOCOUNT);
	}

	if (_dwarf_generate_sections(dbg, error) != DW_DLE_NONE)
		return (DW_DLV_NOCOUNT);

	return (dbg->dbgp_seccnt);
}