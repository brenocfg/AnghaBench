#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  hubname ;
struct TYPE_8__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_7__ {int BridgeMode; int LinkModeServer; int SecureNATMode; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * GetHub (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* GetSessionByName (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  MAX_SESSION_NAME_LEN ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_1__*) ; 
 int /*<<< orphan*/  StopSession (TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ ) ; 

void SiCalledDeleteSession(SERVER *s, PACK *p)
{
	char name[MAX_SESSION_NAME_LEN + 1];
	char hubname[MAX_HUBNAME_LEN + 1];
	HUB *h;
	SESSION *sess;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	if (PackGetStr(p, "HubName", hubname, sizeof(hubname)) == false)
	{
		return;
	}
	if (PackGetStr(p, "SessionName", name, sizeof(name)) == false)
	{
		return;
	}

	LockHubList(s->Cedar);
	{
		h = GetHub(s->Cedar, hubname);
	}
	UnlockHubList(s->Cedar);

	if (h == NULL)
	{
		return;
	}

	sess = GetSessionByName(h, name);

	if (sess != NULL)
	{
		if (sess->BridgeMode == false && sess->LinkModeServer == false && sess->SecureNATMode == false)
		{
			StopSession(sess);
		}
		ReleaseSession(sess);
	}

	ReleaseHub(h);
}