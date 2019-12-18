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
typedef  size_t UINT ;
struct TYPE_5__ {size_t num_value; TYPE_1__** values; } ;
struct TYPE_4__ {void* Data; } ;
typedef  TYPE_2__ ELEMENT ;

/* Variables and functions */

void *GetDataValue(ELEMENT *e, UINT index)
{
	// Validate arguments
	if (e == NULL)
	{
		return NULL;
	}
	if (e->values == NULL)
	{
		return NULL;
	}
	if (index >= e->num_value)
	{
		return NULL;
	}
	if (e->values[index] == NULL)
	{
		return NULL;
	}

	return e->values[index]->Data;
}