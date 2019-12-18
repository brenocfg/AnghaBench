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
struct _Dwarf_P_Expr_Entry {int /*<<< orphan*/  ee_sym; } ;
struct TYPE_4__ {int /*<<< orphan*/  pe_length; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Expr ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLV_NOCOUNT ; 
 int /*<<< orphan*/  DW_OP_addr ; 
 struct _Dwarf_P_Expr_Entry* _dwarf_add_expr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Dwarf_Unsigned
dwarf_add_expr_addr_b(Dwarf_P_Expr expr, Dwarf_Unsigned address,
    Dwarf_Unsigned sym_index, Dwarf_Error *error)
{
	struct _Dwarf_P_Expr_Entry *ee;

	if (expr == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_NOCOUNT);
	}

	if ((ee = _dwarf_add_expr(expr, DW_OP_addr, address, 0, error)) == NULL)
		return (DW_DLV_NOCOUNT);

	ee->ee_sym = sym_index;

	return (expr->pe_length);
}