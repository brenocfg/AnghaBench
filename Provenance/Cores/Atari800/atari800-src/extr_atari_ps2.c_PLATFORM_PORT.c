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
 int INPUT_STICK_BACK ; 
 int INPUT_STICK_FORWARD ; 
 int INPUT_STICK_LEFT ; 
 int INPUT_STICK_RIGHT ; 
 int PAD_DOWN ; 
 int PAD_LEFT ; 
 int PAD_RIGHT ; 
 int PAD_UP ; 
 int PadButtons () ; 

int PLATFORM_PORT(int num)
{
	int ret = 0xff;
	if (num == 0) {
		int pad = PadButtons();
		if (pad & PAD_LEFT)
			ret &= 0xf0 | INPUT_STICK_LEFT;
		if (pad & PAD_RIGHT)
			ret &= 0xf0 | INPUT_STICK_RIGHT;
		if (pad & PAD_UP)
			ret &= 0xf0 | INPUT_STICK_FORWARD;
		if (pad & PAD_DOWN)
			ret &= 0xf0 | INPUT_STICK_BACK;
	}
	return ret;
}