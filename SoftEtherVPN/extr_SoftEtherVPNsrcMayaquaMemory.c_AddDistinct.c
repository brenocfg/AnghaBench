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
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ IsInList (int /*<<< orphan*/ *,void*) ; 

void AddDistinct(LIST *o, void *p)
{
	// Validate arguments
	if (o == NULL || p == NULL)
	{
		return;
	}

	if (IsInList(o, p))
	{
		return;
	}

	Add(o, p);
}