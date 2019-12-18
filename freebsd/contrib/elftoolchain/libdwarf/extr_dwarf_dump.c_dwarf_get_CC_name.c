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
#define  DW_CC_hi_user 132 
#define  DW_CC_lo_user 131 
#define  DW_CC_nocall 130 
#define  DW_CC_normal 129 
#define  DW_CC_program 128 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_CC_name(unsigned cc, const char **s)
{

	assert(s != NULL);

	switch (cc) {
	case DW_CC_normal:
		*s = "DW_CC_normal"; break;
	case DW_CC_program:
		*s = "DW_CC_program"; break;
	case DW_CC_nocall:
		*s = "DW_CC_nocall"; break;
	case DW_CC_lo_user:
		*s = "DW_CC_lo_user"; break;
	case DW_CC_hi_user:
		*s = "DW_CC_hi_user"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}