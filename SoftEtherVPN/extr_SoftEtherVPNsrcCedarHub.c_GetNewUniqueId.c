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
typedef  int UINT ;
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * SearchSessionByUniqueId (int /*<<< orphan*/ *,int) ; 

UINT GetNewUniqueId(HUB *h)
{
	UINT id;
	// Validate arguments
	if (h == NULL)
	{
		return 0;
	}

	for (id = 1;;id++)
	{
		if (SearchSessionByUniqueId(h, id) == NULL)
		{
			return id;
		}
	}
}