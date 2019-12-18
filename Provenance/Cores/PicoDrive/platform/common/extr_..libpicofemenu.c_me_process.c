#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int beh; scalar_t__ var; scalar_t__ data; scalar_t__ min; scalar_t__ max; } ;
typedef  TYPE_1__ menu_entry ;

/* Variables and functions */
#define  MB_OPT_CUSTONOFF 132 
#define  MB_OPT_CUSTRANGE 131 
#define  MB_OPT_ENUM 130 
#define  MB_OPT_ONOFF 129 
#define  MB_OPT_RANGE 128 
 int /*<<< orphan*/  me_toggle_onoff (TYPE_1__*) ; 

__attribute__((used)) static int me_process(menu_entry *entry, int is_next, int is_lr)
{
	const char **names;
	int c;
	switch (entry->beh)
	{
		case MB_OPT_ONOFF:
		case MB_OPT_CUSTONOFF:
			me_toggle_onoff(entry);
			return 1;
		case MB_OPT_RANGE:
		case MB_OPT_CUSTRANGE:
			c = is_lr ? 10 : 1;
			*(int *)entry->var += is_next ? c : -c;
			if (*(int *)entry->var < (int)entry->min)
				*(int *)entry->var = (int)entry->max;
			if (*(int *)entry->var > (int)entry->max)
				*(int *)entry->var = (int)entry->min;
			return 1;
		case MB_OPT_ENUM:
			names = (const char **)entry->data;
			for (c = 0; names[c] != NULL; c++)
				;
			*(signed char *)entry->var += is_next ? 1 : -1;
			if (*(signed char *)entry->var < 0)
				*(signed char *)entry->var = 0;
			if (*(signed char *)entry->var >= c)
				*(signed char *)entry->var = c - 1;
			return 1;
		default:
			return 0;
	}
}