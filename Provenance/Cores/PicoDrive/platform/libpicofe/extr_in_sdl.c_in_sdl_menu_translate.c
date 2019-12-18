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
struct menu_keymap {int pbtn; int key; } ;
struct in_sdl_state {scalar_t__ joy; TYPE_1__* drv; } ;
struct in_pdata {char** key_names; int jmap_size; int kmap_size; struct menu_keymap* key_map; struct menu_keymap* joy_map; } ;
struct TYPE_2__ {struct in_pdata* pdata; } ;

/* Variables and functions */
 int PBTN_CHAR ; 
 unsigned int SDLK_LAST ; 
 char** in_sdl_keys ; 

__attribute__((used)) static int in_sdl_menu_translate(void *drv_data, int keycode, char *charcode)
{
	struct in_sdl_state *state = drv_data;
	const struct in_pdata *pdata = state->drv->pdata;
	const char * const * key_names = in_sdl_keys;
	const struct menu_keymap *map;
	int map_len;
	int ret = 0;
	int i;

	if (pdata->key_names)
		key_names = pdata->key_names;

	if (state->joy) {
		map = pdata->joy_map;
		map_len = pdata->jmap_size;
	} else {
		map = pdata->key_map;
		map_len = pdata->kmap_size;
	}

	if (keycode < 0)
	{
		/* menu -> kc */
		keycode = -keycode;
		for (i = 0; i < map_len; i++)
			if (map[i].pbtn == keycode)
				return map[i].key;
	}
	else
	{
		for (i = 0; i < map_len; i++) {
			if (map[i].key == keycode) {
				ret = map[i].pbtn;
				break;
			}
		}

		if (charcode != NULL && (unsigned int)keycode < SDLK_LAST &&
		    key_names[keycode] != NULL && key_names[keycode][1] == 0)
		{
			ret |= PBTN_CHAR;
			*charcode = key_names[keycode][0];
		}
	}

	return ret;
}