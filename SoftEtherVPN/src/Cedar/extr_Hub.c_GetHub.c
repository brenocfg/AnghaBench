#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_9__ {char* Name; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ HUB ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (TYPE_2__*) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockHubList (TYPE_2__*) ; 

HUB *GetHub(CEDAR *cedar, char *name)
{
	HUB *h, t;
	// Validate arguments
	if (cedar == NULL || name == NULL)
	{
		return NULL;
	}

	LockHubList(cedar);

	t.Name = name;
	h = Search(cedar->HubList, &t);
	if (h == NULL)
	{
		UnlockHubList(cedar);
		return NULL;
	}

	AddRef(h->ref);

	UnlockHubList(cedar);

	return h;
}