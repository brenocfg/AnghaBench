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
typedef  int /*<<< orphan*/  HASH_LIST ;

/* Variables and functions */
 int /*<<< orphan*/ * HashListKeyToPointer (int /*<<< orphan*/ *,scalar_t__) ; 

bool IsInHashListKey(HASH_LIST *h, UINT key)
{
	// Validate arguments
	if (h == NULL || key == 0)
	{
		return false;
	}

	if (HashListKeyToPointer(h, key) == NULL)
	{
		return false;
	}

	return true;
}