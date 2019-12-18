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
#define  DW_DS_leading_overpunch 132 
#define  DW_DS_leading_separate 131 
#define  DW_DS_trailing_overpunch 130 
#define  DW_DS_trailing_separate 129 
#define  DW_DS_unsigned 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_DS_name(unsigned ds, const char **s)
{

	assert(s != NULL);

	switch (ds) {
	case DW_DS_unsigned:
		*s = "DW_DS_unsigned"; break;
	case DW_DS_leading_overpunch:
		*s = "DW_DS_leading_overpunch"; break;
	case DW_DS_trailing_overpunch:
		*s = "DW_DS_trailing_overpunch"; break;
	case DW_DS_leading_separate:
		*s = "DW_DS_leading_separate"; break;
	case DW_DS_trailing_separate:
		*s = "DW_DS_trailing_separate";
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}