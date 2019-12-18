#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_14__ {TYPE_2__* Session; int /*<<< orphan*/  Protocol; } ;
struct TYPE_13__ {TYPE_1__* Option; TYPE_2__* ServerSession; int /*<<< orphan*/  Hub; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  Policy; } ;
struct TYPE_12__ {int LinkModeServer; int /*<<< orphan*/  Hub; int /*<<< orphan*/  Name; int /*<<< orphan*/  ref; int /*<<< orphan*/  Username; TYPE_3__* Link; } ;
struct TYPE_11__ {int /*<<< orphan*/  AccountName; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ SESSION ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  TYPE_3__ LINK ;
typedef  TYPE_4__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTION_HUB_LINK_SERVER ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  LINK_USER_NAME ; 
 int /*<<< orphan*/  LINK_USER_NAME_PRINT ; 
 int MAX_SIZE ; 
 TYPE_4__* NewServerConnection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* NewServerSession (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseConnection (TYPE_4__*) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_2__*) ; 
 int /*<<< orphan*/  SessionMain (TYPE_2__*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

void LinkServerSessionThread(THREAD *t, void *param)
{
	LINK *k = (LINK *)param;
	CONNECTION *c;
	SESSION *s;
	POLICY *policy;
	wchar_t name[MAX_SIZE];
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	// Create a server connection
	c = NewServerConnection(k->Cedar, NULL, t);
	c->Protocol = CONNECTION_HUB_LINK_SERVER;

	// Create a policy
	policy = ZeroMalloc(sizeof(POLICY));
	Copy(policy, k->Policy, sizeof(POLICY));

	// Create a server session
	s = NewServerSession(k->Cedar, c, k->Hub, LINK_USER_NAME, policy);
	s->LinkModeServer = true;
	s->Link = k;
	c->Session = s;
	ReleaseConnection(c);

	// User name
	s->Username = CopyStr(LINK_USER_NAME_PRINT);

	k->ServerSession = s;
	AddRef(k->ServerSession->ref);

	// Notify the initialization completion
	NoticeThreadInit(t);

	UniStrCpy(name, sizeof(name), k->Option->AccountName);
	HLog(s->Hub, "LH_LINK_START", name, s->Name);

	// Main function of session
	SessionMain(s);

	HLog(s->Hub, "LH_LINK_STOP", name);

	ReleaseSession(s);
}