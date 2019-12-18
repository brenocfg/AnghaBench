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
#define  MTA_CD1400 133 
#define  SXDC 132 
#define  TA4 131 
#define  TA4_ASIC 130 
#define  TA8 129 
#define  TA8_ASIC 128 

__attribute__((used)) static char *mod_type_s(int module_type)
{
	switch (module_type) {
	case TA4:
		return "TA4";
	case TA8:
		return "TA8";
	case TA4_ASIC:
		return "TA4_ASIC";
	case TA8_ASIC:
		return "TA8_ASIC";
	case MTA_CD1400:
		return "MTA_CD1400";
	case SXDC:
		return "SXDC";
	default:
		return "Unknown/invalid";
	}
}