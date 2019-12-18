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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  IntValue; } ;
typedef  TYPE_1__ PARAM_VALUE ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 TYPE_1__* FindParamValue (int /*<<< orphan*/ *,char*) ; 

UINT GetParamInt(LIST *o, char *name)
{
	PARAM_VALUE *v;
	// Validate arguments
	if (o == NULL)
	{
		return 0;
	}

	v = FindParamValue(o, name);
	if (v == NULL)
	{
		return 0;
	}
	else
	{
		return v->IntValue;
	}
}