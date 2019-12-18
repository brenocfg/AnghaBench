#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* dt_provmod; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_5__ {char* dp_name; struct TYPE_5__* dp_next; } ;
typedef  TYPE_2__ dt_provmod_t ;

/* Variables and functions */

int
dtrace_provider_modules(dtrace_hdl_t *dtp, const char **mods, int nmods)
{
	dt_provmod_t *prov;
	int i = 0;

	for (prov = dtp->dt_provmod; prov != NULL; prov = prov->dp_next, i++) {
		if (i < nmods)
			mods[i] = prov->dp_name;
	}

	return (i);
}