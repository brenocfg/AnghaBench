#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ at_form; TYPE_1__* u; TYPE_2__* at_die; } ;
struct TYPE_9__ {int /*<<< orphan*/  signature; } ;
struct TYPE_8__ {int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_7__ {int u64; int /*<<< orphan*/  u8p; } ;
typedef  TYPE_3__ Dwarf_Sig8 ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_4__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_ATTR_FORM_BAD ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 scalar_t__ DW_FORM_ref_sig8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
dwarf_formsig8(Dwarf_Attribute at, Dwarf_Sig8 *return_sig8, Dwarf_Error *error)
{
	Dwarf_Debug dbg;

	dbg = at != NULL ? at->at_die->die_dbg : NULL;

	if (at == NULL || return_sig8 == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}
	
	if (at->at_form != DW_FORM_ref_sig8) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ATTR_FORM_BAD);
		return (DW_DLV_ERROR);
	}

	assert(at->u[0].u64 == 8);
	memcpy(return_sig8->signature, at->u[1].u8p, at->u[0].u64);

	return (DW_DLV_OK);
}