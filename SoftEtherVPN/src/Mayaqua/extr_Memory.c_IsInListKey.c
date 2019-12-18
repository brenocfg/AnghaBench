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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 void* ListKeyToPointer (int /*<<< orphan*/ *,scalar_t__) ; 

bool IsInListKey(LIST *o, UINT key)
{
	void *p;
	// Validate arguments
	if (o == NULL || key == 0)
	{
		return false;
	}

	p = ListKeyToPointer(o, key);
	if (p == NULL)
	{
		return false;
	}

	return true;
}