#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/ * GetIniEntry (int /*<<< orphan*/ *,char*) ; 

bool EntryListHasKey(LIST *o, char *key)
{
	// Validate arguments
	if (o == NULL || key == NULL)
	{
		return false;
	}

	if (GetIniEntry(o, key) != NULL)
	{
		return true;
	}

	return false;
}