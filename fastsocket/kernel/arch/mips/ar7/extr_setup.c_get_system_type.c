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
typedef  int u16 ;

/* Variables and functions */
#define  AR7_CHIP_7100 130 
#define  AR7_CHIP_7200 129 
#define  AR7_CHIP_7300 128 
 int ar7_chip_id () ; 

const char *get_system_type(void)
{
	u16 chip_id = ar7_chip_id();
	switch (chip_id) {
	case AR7_CHIP_7300:
		return "TI AR7 (TNETD7300)";
	case AR7_CHIP_7100:
		return "TI AR7 (TNETD7100)";
	case AR7_CHIP_7200:
		return "TI AR7 (TNETD7200)";
	default:
		return "TI AR7 (Unknown)";
	}
}