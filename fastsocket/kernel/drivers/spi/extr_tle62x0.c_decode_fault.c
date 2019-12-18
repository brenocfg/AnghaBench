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
#define  DIAG_NORMAL 131 
#define  DIAG_OPEN 130 
#define  DIAG_OVERLOAD 129 
#define  DIAG_SHORTGND 128 

__attribute__((used)) static unsigned char *decode_fault(unsigned int fault_code)
{
	fault_code &= 3;

	switch (fault_code) {
	case DIAG_NORMAL:
		return "N";
	case DIAG_OVERLOAD:
		return "V";
	case DIAG_OPEN:
		return "O";
	case DIAG_SHORTGND:
		return "G";
	}

	return "?";
}