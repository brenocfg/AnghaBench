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
typedef  int /*<<< orphan*/  HUB ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * GetHub (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 

bool IsHub(CEDAR *cedar, char *name)
{
	HUB *h;
	// Validate arguments
	if (cedar == NULL || name == NULL)
	{
		return false;
	}

	h = GetHub(cedar, name);
	if (h == NULL)
	{
		return false;
	}

	ReleaseHub(h);

	return true;
}