#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct _Dwarf_P_Expr {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  dbgp_pelist; } ;
struct TYPE_9__ {TYPE_2__* pe_dbg; int /*<<< orphan*/  pe_eelist; } ;
typedef  TYPE_1__* Dwarf_P_Expr ;
typedef  TYPE_2__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_MEMORY ; 
 TYPE_1__* DW_DLV_BADADDR ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  pe_next ; 

Dwarf_P_Expr
dwarf_new_expr(Dwarf_P_Debug dbg, Dwarf_Error *error)
{
	Dwarf_P_Expr pe;

	if (dbg == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_BADADDR);
	}

	if ((pe = calloc(1, sizeof(struct _Dwarf_P_Expr))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLV_BADADDR);
	}
	STAILQ_INIT(&pe->pe_eelist);

	STAILQ_INSERT_TAIL(&dbg->dbgp_pelist, pe, pe_next);
	pe->pe_dbg = dbg;

	return (pe);
}