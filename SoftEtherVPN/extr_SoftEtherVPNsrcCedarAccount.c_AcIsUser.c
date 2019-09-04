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
typedef  int /*<<< orphan*/  USER ;
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * AcGetUser (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ NO_ACCOUNT_DB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseUser (int /*<<< orphan*/ *) ; 

bool AcIsUser(HUB *h, char *name)
{
	USER *u;
	// Validate arguments
	if (h == NULL || name == NULL || NO_ACCOUNT_DB(h))
	{
		return false;
	}

	u = AcGetUser(h, name);
	if (u == NULL)
	{
		return false;
	}
	ReleaseUser(u);

	return true;
}