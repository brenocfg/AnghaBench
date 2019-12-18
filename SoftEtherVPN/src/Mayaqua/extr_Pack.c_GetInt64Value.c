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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  size_t UINT ;
struct TYPE_5__ {size_t num_value; TYPE_1__** values; } ;
struct TYPE_4__ {int /*<<< orphan*/  Int64Value; } ;
typedef  TYPE_2__ ELEMENT ;

/* Variables and functions */

UINT64 GetInt64Value(ELEMENT *e, UINT index)
{
	// Validate arguments
	if (e == NULL)
	{
		return 0;
	}
	if (index >= e->num_value)
	{
		return 0;
	}
	if (e->values[index] == NULL)
	{
		return 0;
	}

	return e->values[index]->Int64Value;
}