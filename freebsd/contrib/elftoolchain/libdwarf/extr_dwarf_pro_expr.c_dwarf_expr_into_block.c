#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pe_block; int /*<<< orphan*/  pe_length; scalar_t__ pe_invalid; int /*<<< orphan*/ * pe_dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Expr ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 scalar_t__ DW_DLE_NONE ; 
 scalar_t__ DW_DLV_BADADDR ; 
 scalar_t__ _dwarf_expr_into_block (TYPE_1__*,int /*<<< orphan*/ *) ; 

Dwarf_Addr
dwarf_expr_into_block(Dwarf_P_Expr expr, Dwarf_Unsigned *length,
    Dwarf_Error *error)
{
	Dwarf_Debug dbg;

	dbg = expr != NULL ? expr->pe_dbg : NULL;

	if (expr == NULL || length == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return ((Dwarf_Addr) (uintptr_t) DW_DLV_BADADDR);
	}

	if (expr->pe_block == NULL || expr->pe_invalid)
		if (_dwarf_expr_into_block(expr, error) != DW_DLE_NONE)
			return ((Dwarf_Addr) (uintptr_t) DW_DLV_BADADDR);

	*length = expr->pe_length;

	return ((Dwarf_Addr) (uintptr_t) expr->pe_block);
}