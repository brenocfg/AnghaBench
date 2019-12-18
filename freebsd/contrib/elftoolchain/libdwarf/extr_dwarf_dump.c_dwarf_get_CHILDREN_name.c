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
#define  DW_CHILDREN_no 129 
#define  DW_CHILDREN_yes 128 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_CHILDREN_name(unsigned children, const char **s)
{

	assert(s != NULL);

	switch (children) {
	case DW_CHILDREN_no:
		*s = "DW_CHILDREN_no"; break;
	case DW_CHILDREN_yes:
		*s = "DW_CHILDREN_yes"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}