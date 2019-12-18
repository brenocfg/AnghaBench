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
 int PBTN_CHAR ; 
 int in_update_keycode (int*,int*,char*,int) ; 
 int menu_key_state ; 
 int menu_last_used_dev ; 

int in_menu_wait_any(char *charcode, int timeout_ms)
{
	int keys_old = menu_key_state;
	int ret;

	while (1)
	{
		int code, is_down = 0, dev_id = 0;

		code = in_update_keycode(&dev_id, &is_down, charcode, timeout_ms);
		if (code < 0)
			break;

		if (keys_old != menu_key_state) {
			menu_last_used_dev = dev_id;
			break;
		}
	}

	ret = menu_key_state;
	menu_key_state &= ~PBTN_CHAR;
	return ret;
}