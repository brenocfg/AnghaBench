#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USER ;
struct TYPE_6__ {TYPE_1__* HubDb; } ;
struct TYPE_5__ {int /*<<< orphan*/  UserList; } ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * AcGetUser (TYPE_2__*,char*) ; 
 scalar_t__ Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseUser (int /*<<< orphan*/ *) ; 

bool AcDeleteUser(HUB *h, char *name)
{
	USER *u;
	// Validate arguments
	if (h == NULL || name == NULL)
	{
		return false;
	}

	u = AcGetUser(h, name);
	if (u == NULL)
	{
		return false;
	}

	if (Delete(h->HubDb->UserList, u))
	{
		ReleaseUser(u);
	}

	ReleaseUser(u);

	return true;
}