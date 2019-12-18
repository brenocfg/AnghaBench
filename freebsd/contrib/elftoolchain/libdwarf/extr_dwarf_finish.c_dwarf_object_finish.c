#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;

/* Variables and functions */
 int DW_DLV_OK ; 
 int /*<<< orphan*/  _dwarf_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int
dwarf_object_finish(Dwarf_Debug dbg, Dwarf_Error *error)
{
	(void) error;	/* unused */

	if (dbg == NULL)
		return (DW_DLV_OK);

	_dwarf_deinit(dbg);

	free(dbg);

	return (DW_DLV_OK);
}