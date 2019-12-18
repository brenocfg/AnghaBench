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
#define  DW_MACINFO_define 132 
#define  DW_MACINFO_end_file 131 
#define  DW_MACINFO_start_file 130 
#define  DW_MACINFO_undef 129 
#define  DW_MACINFO_vendor_ext 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_MACINFO_name(unsigned mi, const char **s)
{

	assert(s != NULL);

	switch (mi) {
	case DW_MACINFO_define:
		*s = "DW_MACINFO_define"; break;
	case DW_MACINFO_undef:
		*s = "DW_MACINFO_undef"; break;
	case DW_MACINFO_start_file:
		*s = "DW_MACINFO_start_file"; break;
	case DW_MACINFO_end_file:
		*s = "DW_MACINFO_end_file"; break;
	case DW_MACINFO_vendor_ext:
		*s = "DW_MACINFO_vendor_ext"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}