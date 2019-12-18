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
#define  MOD_2_PARALLEL 137 
#define  MOD_2_RS232DB25 136 
#define  MOD_2_RS232RJ45 135 
#define  MOD_2_RS422DB25 134 
#define  MOD_BLANK 133 
#define  MOD_PARALLEL 132 
#define  MOD_RS232DB25 131 
#define  MOD_RS232DB25MALE 130 
#define  MOD_RS232RJ45 129 
#define  MOD_RS422DB25 128 

__attribute__((used)) static char *pan_type_s(int pan_type)
{
	switch (pan_type) {
	case MOD_RS232DB25:
		return "MOD_RS232DB25";
	case MOD_RS232RJ45:
		return "MOD_RS232RJ45";
	case MOD_RS422DB25:
		return "MOD_RS422DB25";
	case MOD_PARALLEL:
		return "MOD_PARALLEL";
	case MOD_2_RS232DB25:
		return "MOD_2_RS232DB25";
	case MOD_2_RS232RJ45:
		return "MOD_2_RS232RJ45";
	case MOD_2_RS422DB25:
		return "MOD_2_RS422DB25";
	case MOD_RS232DB25MALE:
		return "MOD_RS232DB25MALE";
	case MOD_2_PARALLEL:
		return "MOD_2_PARALLEL";
	case MOD_BLANK:
		return "empty";
	default:
		return "invalid";
	}
}