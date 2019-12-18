#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_3__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 int /*<<< orphan*/  DelHubEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * GetHub (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetHubOffline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ ) ; 

void SiCalledDeleteHub(SERVER *s, PACK *p)
{
	char name[MAX_SIZE];
	HUB *h;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	if (PackGetStr(p, "HubName", name, sizeof(name)) == false)
	{
		return;
	}

	LockHubList(s->Cedar);

	h = GetHub(s->Cedar, name);
	if (h == NULL)
	{
		UnlockHubList(s->Cedar);
		return;
	}
	UnlockHubList(s->Cedar);

	SetHubOffline(h);

	LockHubList(s->Cedar);

	DelHubEx(s->Cedar, h, true);

	UnlockHubList(s->Cedar);

	ReleaseHub(h);
}