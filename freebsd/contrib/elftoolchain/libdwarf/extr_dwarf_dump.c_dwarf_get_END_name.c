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
#define  DW_END_big 132 
#define  DW_END_default 131 
#define  DW_END_high_user 130 
#define  DW_END_little 129 
#define  DW_END_lo_user 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_END_name(unsigned end, const char **s)
{

	assert(s != NULL);

	switch (end) {
	case DW_END_default:
		*s = "DW_END_default"; break;
	case DW_END_big:
		*s = "DW_END_big"; break;
	case DW_END_little:
		*s = "DW_END_little"; break;
	case DW_END_lo_user:
		*s = "DW_END_lo_user"; break;
	case DW_END_high_user:
		*s = "DW_END_high_user"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}