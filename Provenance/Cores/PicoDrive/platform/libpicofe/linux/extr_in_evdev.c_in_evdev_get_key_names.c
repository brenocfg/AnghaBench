#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in_pdata {char const* const* key_names; } ;
struct TYPE_3__ {struct in_pdata* pdata; } ;
typedef  TYPE_1__ in_drv_t ;

/* Variables and functions */
 int KEY_CNT ; 
 char const* const* in_evdev_keys ; 

__attribute__((used)) static const char * const *
in_evdev_get_key_names(const in_drv_t *drv, int *count)
{
	const struct in_pdata *pdata = drv->pdata;
	*count = KEY_CNT;

	if (pdata->key_names)
		return pdata->key_names;
	return in_evdev_keys;
}