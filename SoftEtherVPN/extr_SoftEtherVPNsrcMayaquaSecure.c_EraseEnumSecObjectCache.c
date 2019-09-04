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
struct TYPE_3__ {int /*<<< orphan*/ * EnumCache; } ;
typedef  TYPE_1__ SECURE ;

/* Variables and functions */
 int /*<<< orphan*/  FreeEnumSecObject (int /*<<< orphan*/ *) ; 

void EraseEnumSecObjectCache(SECURE *sec)
{
	// Validate arguments
	if (sec == NULL || sec->EnumCache == NULL)
	{
		return;
	}

	FreeEnumSecObject(sec->EnumCache);
	sec->EnumCache = NULL;
}