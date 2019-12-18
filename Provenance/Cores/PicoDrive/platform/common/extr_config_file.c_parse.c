#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* name; scalar_t__ beh; int mask; int min; int max; scalar_t__ var; scalar_t__ data; int /*<<< orphan*/  need_to_save; } ;
typedef  TYPE_1__ menu_entry ;
struct TYPE_7__ {int /*<<< orphan*/  volume; } ;

/* Variables and functions */
 scalar_t__ MB_OPT_ENUM ; 
 scalar_t__ MB_OPT_ONOFF ; 
 scalar_t__ MB_OPT_RANGE ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 TYPE_5__ currentConfig ; 
 scalar_t__ custom_read (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  lprintf (char*,char const*,...) ; 
 TYPE_1__* me_list_get_first () ; 
 TYPE_1__* me_list_get_next () ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse(const char *var, const char *val, int *keys_encountered)
{
	menu_entry *me;
	int tmp;

	if (strcasecmp(var, "LastUsedROM") == 0)
		return; /* handled elsewhere */

	if (strncasecmp(var, "bind", 4) == 0) {
		*keys_encountered = 1;
		return; /* handled elsewhere */
	}

	if (strcasecmp(var, "Sound Volume") == 0) {
		currentConfig.volume = atoi(val);
		return;
	}

	for (me = me_list_get_first(); me != NULL; me = me_list_get_next())
	{
		char *p;

		if (!me->need_to_save)
			continue;
		if (me->name == NULL || strcasecmp(var, me->name) != 0)
			continue;

		if (me->beh == MB_OPT_ONOFF) {
			tmp = strtol(val, &p, 0);
			if (*p != 0)
				goto bad_val;
			if (tmp) *(int *)me->var |=  me->mask;
			else     *(int *)me->var &= ~me->mask;
			return;
		}
		else if (me->beh == MB_OPT_RANGE) {
			tmp = strtol(val, &p, 0);
			if (*p != 0)
				goto bad_val;
			if (tmp < me->min) tmp = me->min;
			if (tmp > me->max) tmp = me->max;
			*(int *)me->var = tmp;
			return;
		}
		else if (me->beh == MB_OPT_ENUM) {
			const char **names, *p1;
			int i;

			names = (const char **)me->data;
			if (names == NULL)
				goto bad_val;
			for (i = 0; names[i] != NULL; i++) {
				for (p1 = names[i]; *p1 == ' '; p1++)
					;
				if (strcasecmp(p1, val) == 0) {
					*(int *)me->var = i;
					return;
				}
			}
			goto bad_val;
		}
		else if (custom_read(me, var, val))
			return;
	}

	lprintf("config_readsect: unhandled var: \"%s\"\n", var);
	return;

bad_val:
	lprintf("config_readsect: unhandled val for \"%s\": \"%s\"\n", var, val);
}