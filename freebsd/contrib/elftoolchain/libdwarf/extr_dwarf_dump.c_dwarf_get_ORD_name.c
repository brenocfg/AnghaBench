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
#define  DW_ORD_col_major 129 
#define  DW_ORD_row_major 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_ORD_name(unsigned ord, const char **s)
{

	assert(s != NULL);

	switch (ord) {
	case DW_ORD_row_major:
		*s = "DW_ORD_row_major"; break;
	case DW_ORD_col_major:
		*s = "DW_ORD_col_major"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}