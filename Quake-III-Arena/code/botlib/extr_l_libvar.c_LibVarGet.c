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
struct TYPE_4__ {int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ libvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* libvarlist ; 

libvar_t *LibVarGet(char *var_name)
{
	libvar_t *v;

	for (v = libvarlist; v; v = v->next)
	{
		if (!Q_stricmp(v->name, var_name))
		{
			return v;
		} //end if
	} //end for
	return NULL;
}