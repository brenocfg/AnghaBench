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
#define  DW_LNE_define_file 132 
#define  DW_LNE_end_sequence 131 
#define  DW_LNE_hi_user 130 
#define  DW_LNE_lo_user 129 
#define  DW_LNE_set_address 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_LNE_name(unsigned lne, const char **s)
{

	assert(s != NULL);

	switch (lne) {
	case DW_LNE_end_sequence:
		*s = "DW_LNE_end_sequence"; break;
	case DW_LNE_set_address:
		*s = "DW_LNE_set_address"; break;
	case DW_LNE_define_file:
		*s = "DW_LNE_define_file"; break;
	case DW_LNE_lo_user:
		*s = "DW_LNE_lo_user"; break;
	case DW_LNE_hi_user:
		*s = "DW_LNE_hi_user"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}