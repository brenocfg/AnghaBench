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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int /*<<< orphan*/  modified; } ;
typedef  TYPE_1__ libvar_t ;

/* Variables and functions */
 TYPE_1__* LibVarGet (char*) ; 
 int /*<<< orphan*/  qfalse ; 

qboolean LibVarChanged(char *var_name)
{
	libvar_t *v;

	v = LibVarGet(var_name);
	if (v)
	{
		return v->modified;
	} //end if
	else
	{
		return qfalse;
	} //end else
}