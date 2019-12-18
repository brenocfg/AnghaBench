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
struct _Dwarf_Debug {int dummy; } ;
struct TYPE_5__ {int dbg_mode; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 TYPE_1__* calloc (int,int) ; 

int
_dwarf_alloc(Dwarf_Debug *ret_dbg, int mode, Dwarf_Error *error)
{
	Dwarf_Debug dbg;

	if ((dbg = calloc(sizeof(struct _Dwarf_Debug), 1)) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	dbg->dbg_mode = mode;

	*ret_dbg = dbg;

	return (DW_DLE_NONE);
}