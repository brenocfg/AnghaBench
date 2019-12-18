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
#define  DW_INL_declared_inlined 131 
#define  DW_INL_declared_not_inlined 130 
#define  DW_INL_inlined 129 
#define  DW_INL_not_inlined 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_INL_name(unsigned inl, const char **s)
{

	assert(s != NULL);

	switch (inl) {
	case DW_INL_not_inlined:
		*s = "DW_INL_not_inlined"; break;
	case DW_INL_inlined:
		*s = "DW_INL_inlined"; break;
	case DW_INL_declared_not_inlined:
		*s = "DW_INL_declared_not_inlined"; break;
	case DW_INL_declared_inlined:
		*s = "DW_INL_declared_inlined"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}