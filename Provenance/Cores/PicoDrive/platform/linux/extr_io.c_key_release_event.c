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
 int /*<<< orphan*/  GP2X_A ; 
 int /*<<< orphan*/  GP2X_B ; 
 int /*<<< orphan*/  GP2X_DOWN ; 
 int /*<<< orphan*/  GP2X_L ; 
 int /*<<< orphan*/  GP2X_LEFT ; 
 int /*<<< orphan*/  GP2X_PUSH ; 
 int /*<<< orphan*/  GP2X_R ; 
 int /*<<< orphan*/  GP2X_RIGHT ; 
 int /*<<< orphan*/  GP2X_SELECT ; 
 int /*<<< orphan*/  GP2X_START ; 
 int /*<<< orphan*/  GP2X_UP ; 
 int /*<<< orphan*/  GP2X_VOL_DOWN ; 
 int /*<<< orphan*/  GP2X_VOL_UP ; 
 int /*<<< orphan*/  GP2X_X ; 
 int /*<<< orphan*/  GP2X_Y ; 
 int /*<<< orphan*/  current_keys ; 

__attribute__((used)) static void key_release_event(int keycode)
{
	switch (keycode)
	{
		case 111:
		case 0x62: current_keys &= ~GP2X_UP;    break;
		case 116:
		case 0x68: current_keys &= ~GP2X_DOWN;  break;
		case 113:
		case 0x64: current_keys &= ~GP2X_LEFT;  break;
		case 114:
		case 0x66: current_keys &= ~GP2X_RIGHT; break;
		case 0x24: current_keys &= ~GP2X_START; break; // enter
		case 0x23: current_keys &= ~GP2X_SELECT;break; // ]
		case 0x34: current_keys &= ~GP2X_A;     break; // z
		case 0x35: current_keys &= ~GP2X_X;     break; // x
		case 0x36: current_keys &= ~GP2X_B;     break; // c
		case 0x37: current_keys &= ~GP2X_Y;     break; // v
		case 0x27: current_keys &= ~GP2X_L;     break; // s
		case 0x28: current_keys &= ~GP2X_R;     break; // d
		case 0x29: current_keys &= ~GP2X_PUSH;  break; // f
		case 0x18: current_keys &= ~GP2X_VOL_DOWN;break; // q
		case 0x19: current_keys &= ~GP2X_VOL_UP;break; // w
	}
}