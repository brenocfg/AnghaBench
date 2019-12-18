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
#define  CYBER9320 143 
#define  CYBER9382 142 
#define  CYBER9385 141 
#define  CYBER9388 140 
#define  CYBER9397 139 
#define  CYBER9397DVD 138 
#define  CYBER9520 137 
#define  CYBER9525DVD 136 
#define  CYBERBLADEAi1 135 
#define  CYBERBLADEAi1D 134 
#define  CYBERBLADEE4 133 
#define  CYBERBLADEXPAi1 132 
#define  CYBERBLADEi1 131 
#define  CYBERBLADEi1D 130 
#define  CYBERBLADEi7 129 
#define  CYBERBLADEi7D 128 

__attribute__((used)) static inline int iscyber(int id)
{
	switch (id) {
	case CYBER9388:
	case CYBER9382:
	case CYBER9385:
	case CYBER9397:
	case CYBER9397DVD:
	case CYBER9520:
	case CYBER9525DVD:
	case CYBERBLADEE4:
	case CYBERBLADEi7D:
	case CYBERBLADEi1:
	case CYBERBLADEi1D:
	case CYBERBLADEAi1:
	case CYBERBLADEAi1D:
	case CYBERBLADEXPAi1:
		return 1;

	case CYBER9320:
	case CYBERBLADEi7:	/* VIA MPV4 integrated version */
	default:
		/* case CYBERBLDAEXPm8:  Strange */
		/* case CYBERBLDAEXPm16: Strange */
		return 0;
	}
}