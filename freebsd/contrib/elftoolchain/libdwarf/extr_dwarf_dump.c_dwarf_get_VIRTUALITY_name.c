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
#define  DW_VIRTUALITY_none 130 
#define  DW_VIRTUALITY_pure_virtual 129 
#define  DW_VIRTUALITY_virtual 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_VIRTUALITY_name(unsigned vir, const char **s)
{

	assert(s != NULL);

	switch (vir) {
	case DW_VIRTUALITY_none:
		*s = "DW_VIRTUALITY_none"; break;
	case DW_VIRTUALITY_virtual:
		*s = "DW_VIRTUALITY_virtual"; break;
	case DW_VIRTUALITY_pure_virtual:
		*s = "DW_VIRTUALITY_pure_virtual"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}