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
#define  DW_ACCESS_private 130 
#define  DW_ACCESS_protected 129 
#define  DW_ACCESS_public 128 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_ACCESS_name(unsigned access, const char **s)
{

	assert(s != NULL);

	switch (access) {
	case DW_ACCESS_public:
		*s = "DW_ACCESS_public"; break;
	case DW_ACCESS_protected:
		*s = "DW_ACCESS_protected"; break;
	case DW_ACCESS_private:
		*s = "DW_ACCESS_private"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}