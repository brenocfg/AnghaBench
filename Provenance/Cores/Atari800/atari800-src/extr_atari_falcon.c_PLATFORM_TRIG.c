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
 int joy0 ; 
 int joy1 ; 
 int /*<<< orphan*/  joyswap ; 
 int trig0 ; 

int PLATFORM_TRIG(int num)
{
	switch (num) {
	case 0:
		return (joy0 > 0x0f) ? 0 : joyswap ? 1 : trig0;
	case 1:
		return (joy1 > 0x0f) ? 0 : joyswap ? trig0 : 1;
	case 2:
	case 3:
	default:
		return 1;
	}
}