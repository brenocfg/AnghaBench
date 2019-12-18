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
typedef  int /*<<< orphan*/  USERGROUP ;
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * AcGetGroup (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ NO_ACCOUNT_DB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseGroup (int /*<<< orphan*/ *) ; 

bool AcIsGroup(HUB *h, char *name)
{
	USERGROUP *g;
	// Validate arguments
	if (h == NULL || name == NULL || NO_ACCOUNT_DB(h))
	{
		return false;
	}

	g = AcGetGroup(h, name);
	if (g == NULL)
	{
		return false;
	}
	ReleaseGroup(g);

	return true;
}