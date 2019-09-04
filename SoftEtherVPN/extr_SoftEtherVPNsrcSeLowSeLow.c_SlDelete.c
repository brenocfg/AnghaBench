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
typedef  size_t UINT ;
struct TYPE_3__ {size_t num_item; void** p; } ;
typedef  TYPE_1__ SL_LIST ;

/* Variables and functions */

bool SlDelete(SL_LIST *o, void *p)
{
	UINT i, n;
	// Validate arguments
	if (o == NULL || p == NULL)
	{
		return false;
	}

	for (i = 0;i < o->num_item;i++)
	{
		if (o->p[i] == p)
		{
			break;
		}
	}
	if (i == o->num_item)
	{
		return false;
	}

	n = i;
	for (i = n;i < (o->num_item - 1);i++)
	{
		o->p[i] = o->p[i + 1];
	}
	o->num_item--;

	return true;
}