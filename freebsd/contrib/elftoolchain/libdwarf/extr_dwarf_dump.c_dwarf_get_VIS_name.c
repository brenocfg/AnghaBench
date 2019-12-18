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

/* Variables and functions */
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
#define  DW_VIS_exported 130 
#define  DW_VIS_local 129 
#define  DW_VIS_qualified 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_VIS_name(unsigned vis, const char **s)
{

	assert(s != NULL);

	switch (vis) {
	case DW_VIS_local:
		*s = "DW_VIS_local"; break;
	case DW_VIS_exported:
		*s = "DW_VIS_exported"; break;
	case DW_VIS_qualified:
		*s = "DW_VIS_qualified"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}