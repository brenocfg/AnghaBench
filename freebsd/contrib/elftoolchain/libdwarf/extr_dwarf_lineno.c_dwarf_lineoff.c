#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ln_column; } ;
typedef  int Dwarf_Signed ;
typedef  TYPE_1__* Dwarf_Line ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 

int
dwarf_lineoff(Dwarf_Line ln, Dwarf_Signed *ret_lineoff, Dwarf_Error *error)
{

	if (ln == NULL || ret_lineoff == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (ln->ln_column == 0)
		*ret_lineoff = -1;
	else
		*ret_lineoff = (Dwarf_Signed) ln->ln_column;

	return (DW_DLV_OK);
}