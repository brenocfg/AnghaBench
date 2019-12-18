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
#define  WM8993_DC_SERVO_0 132 
#define  WM8993_DC_SERVO_READBACK_0 131 
#define  WM8993_DC_SERVO_READBACK_1 130 
#define  WM8993_DC_SERVO_READBACK_2 129 
#define  WM8993_SOFTWARE_RESET 128 

__attribute__((used)) static int wm8993_volatile(unsigned int reg)
{
	switch (reg) {
	case WM8993_SOFTWARE_RESET:
	case WM8993_DC_SERVO_0:
	case WM8993_DC_SERVO_READBACK_0:
	case WM8993_DC_SERVO_READBACK_1:
	case WM8993_DC_SERVO_READBACK_2:
		return 1;
	default:
		return 0;
	}
}