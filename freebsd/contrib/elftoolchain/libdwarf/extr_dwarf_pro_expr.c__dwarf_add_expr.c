#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lr_offset; void* lr_number2; void* lr_number; int /*<<< orphan*/  lr_atom; } ;
struct _Dwarf_P_Expr_Entry {TYPE_1__ ee_loc; } ;
struct TYPE_5__ {int pe_length; int pe_invalid; int /*<<< orphan*/  pe_eelist; int /*<<< orphan*/ * pe_dbg; } ;
typedef  void* Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Small ;
typedef  TYPE_2__* Dwarf_P_Expr ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_MEMORY ; 
 scalar_t__ DW_DLE_NONE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct _Dwarf_P_Expr_Entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ _dwarf_loc_expr_add_atom (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,void*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct _Dwarf_P_Expr_Entry* calloc (int,int) ; 
 int /*<<< orphan*/  ee_next ; 

__attribute__((used)) static struct _Dwarf_P_Expr_Entry *
_dwarf_add_expr(Dwarf_P_Expr expr, Dwarf_Small opcode, Dwarf_Unsigned val1,
    Dwarf_Unsigned val2, Dwarf_Error *error)
{
	struct _Dwarf_P_Expr_Entry *ee;
	Dwarf_Debug dbg;
	int len;

	dbg = expr != NULL ? expr->pe_dbg : NULL;

	if (_dwarf_loc_expr_add_atom(expr->pe_dbg, NULL, NULL, opcode, val1,
	    val2, &len, error) != DW_DLE_NONE)
		return (NULL);
	assert(len > 0);

	if ((ee = calloc(1, sizeof(*ee))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (NULL);
	}

	STAILQ_INSERT_TAIL(&expr->pe_eelist, ee, ee_next);

	ee->ee_loc.lr_atom = opcode;
	ee->ee_loc.lr_number = val1;
	ee->ee_loc.lr_number2 = val2;
	ee->ee_loc.lr_offset = expr->pe_length;
	expr->pe_length += len;
	expr->pe_invalid = 1;

	return (ee);
}