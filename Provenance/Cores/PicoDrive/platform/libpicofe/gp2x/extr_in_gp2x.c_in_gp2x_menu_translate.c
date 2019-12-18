#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pbtn; int key; } ;

/* Variables and functions */
 int KEY_PBTN_MAP_SIZE ; 
 TYPE_1__* key_pbtn_map ; 

__attribute__((used)) static int in_gp2x_menu_translate(void *drv_data, int keycode, char *charcode)
{
	int i;
	if (keycode < 0)
	{
		/* menu -> kc */
		keycode = -keycode;
		for (i = 0; i < KEY_PBTN_MAP_SIZE; i++)
			if (key_pbtn_map[i].pbtn == keycode)
				return key_pbtn_map[i].key;
	}
	else
	{
		for (i = 0; i < KEY_PBTN_MAP_SIZE; i++)
			if (key_pbtn_map[i].key == keycode)
				return key_pbtn_map[i].pbtn;
	}

	return 0;
}