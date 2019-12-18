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
#define  PR_TYPE_EXCLUSIVE_ACCESS 133 
#define  PR_TYPE_EXCLUSIVE_ACCESS_ALLREG 132 
#define  PR_TYPE_EXCLUSIVE_ACCESS_REGONLY 131 
#define  PR_TYPE_WRITE_EXCLUSIVE 130 
#define  PR_TYPE_WRITE_EXCLUSIVE_ALLREG 129 
#define  PR_TYPE_WRITE_EXCLUSIVE_REGONLY 128 

unsigned char *core_scsi3_pr_dump_type(int type)
{
	switch (type) {
	case PR_TYPE_WRITE_EXCLUSIVE:
		return "Write Exclusive Access";
	case PR_TYPE_EXCLUSIVE_ACCESS:
		return "Exclusive Access";
	case PR_TYPE_WRITE_EXCLUSIVE_REGONLY:
		return "Write Exclusive Access, Registrants Only";
	case PR_TYPE_EXCLUSIVE_ACCESS_REGONLY:
		return "Exclusive Access, Registrants Only";
	case PR_TYPE_WRITE_EXCLUSIVE_ALLREG:
		return "Write Exclusive Access, All Registrants";
	case PR_TYPE_EXCLUSIVE_ACCESS_ALLREG:
		return "Exclusive Access, All Registrants";
	default:
		break;
	}

	return "Unknown SPC-3 PR Type";
}