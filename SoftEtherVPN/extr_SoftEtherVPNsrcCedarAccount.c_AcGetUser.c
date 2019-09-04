#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* Name; int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ USER ;
struct TYPE_11__ {TYPE_1__* HubDb; } ;
struct TYPE_9__ {int /*<<< orphan*/  UserList; } ;
typedef  TYPE_3__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 scalar_t__ NO_ACCOUNT_DB (TYPE_3__*) ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 

USER *AcGetUser(HUB *h, char *name)
{
	USER *u, t;
	// Validate arguments
	if (h == NULL || name == NULL || NO_ACCOUNT_DB(h))
	{
		return NULL;
	}

	t.Name = name;
	u = Search(h->HubDb->UserList, &t);
	if (u == NULL)
	{
		return NULL;
	}
	AddRef(u->ref);

	return u;
}