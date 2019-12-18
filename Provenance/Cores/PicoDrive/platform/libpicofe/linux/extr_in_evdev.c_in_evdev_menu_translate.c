#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in_pdata {int kmap_size; TYPE_2__* key_map; } ;
struct TYPE_6__ {int kc_first; int kc_last; TYPE_1__* drv; } ;
typedef  TYPE_3__ in_evdev_t ;
struct TYPE_5__ {int pbtn; int key; } ;
struct TYPE_4__ {struct in_pdata* pdata; } ;

/* Variables and functions */
 unsigned int KEY_CNT ; 
 int PBTN_CHAR ; 
 char** in_evdev_keys ; 

__attribute__((used)) static int in_evdev_menu_translate(void *drv_data, int keycode, char *charcode)
{
	in_evdev_t *dev = drv_data;
	const struct in_pdata *pdata = dev->drv->pdata;
	int ret = 0;
	int i;

	if (keycode < 0)
	{
		/* menu -> kc */
		keycode = -keycode;
		for (i = 0; i < pdata->kmap_size; i++)
			if (pdata->key_map[i].pbtn == keycode) {
				int k = pdata->key_map[i].key;
				/* should really check EVIOCGBIT, but this is enough for now */
				if (dev->kc_first <= k && k <= dev->kc_last)
					return k;
			}
	}
	else
	{
		for (i = 0; i < pdata->kmap_size; i++) {
			if (pdata->key_map[i].key == keycode) {
				ret = pdata->key_map[i].pbtn;
				break;
			}
		}

		if (charcode != NULL && (unsigned int)keycode < KEY_CNT &&
		    in_evdev_keys[keycode] != NULL && in_evdev_keys[keycode][1] == 0)
		{
			char c = in_evdev_keys[keycode][0];
			if ('A' <= c && c <= 'Z')
				c = 'a' + c - 'A';
			ret |= PBTN_CHAR;
			*charcode = c;
		}
	}

	return ret;
}