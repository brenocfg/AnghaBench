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
#define  DW_ID_case_insensitive 131 
#define  DW_ID_case_sensitive 130 
#define  DW_ID_down_case 129 
#define  DW_ID_up_case 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_ID_name(unsigned id, const char **s)
{

	assert(s != NULL);

	switch (id) {
	case DW_ID_case_sensitive:
		*s = "DW_ID_case_sensitive"; break;
	case DW_ID_up_case:
		*s = "DW_ID_up_case"; break;
	case DW_ID_down_case:
		*s = "DW_ID_down_case"; break;
	case DW_ID_case_insensitive:
		*s = "DW_ID_case_insensitive"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}