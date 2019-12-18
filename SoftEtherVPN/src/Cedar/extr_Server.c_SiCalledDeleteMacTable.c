#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hubname ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  MacHashTable; } ;
struct TYPE_6__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  MAC_TABLE_ENTRY ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteHash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 TYPE_2__* GetHub (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * HashListKeyToPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHashList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_2__*) ; 
 int /*<<< orphan*/  UnlockHashList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ ) ; 

void SiCalledDeleteMacTable(SERVER *s, PACK *p)
{
	UINT key;
	char hubname[MAX_HUBNAME_LEN + 1];
	HUB *h;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	if (PackGetStr(p, "HubName", hubname, sizeof(hubname)) == false)
	{
		return;
	}
	key = PackGetInt(p, "Key");

	LockHubList(s->Cedar);
	{
		h = GetHub(s->Cedar, hubname);
	}
	UnlockHubList(s->Cedar);

	if (h == NULL)
	{
		return;
	}

	LockHashList(h->MacHashTable);
	{
		MAC_TABLE_ENTRY *e = HashListKeyToPointer(h->MacHashTable, key);
		DeleteHash(h->MacHashTable, e);
		Free(e);
	}
	UnlockHashList(h->MacHashTable);

	ReleaseHub(h);
}