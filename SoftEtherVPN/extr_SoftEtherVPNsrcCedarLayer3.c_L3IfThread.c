#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  username ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_25__ {TYPE_3__* Session; int /*<<< orphan*/  Protocol; } ;
struct TYPE_24__ {TYPE_3__* Session; TYPE_13__* Hub; TYPE_2__* Switch; } ;
struct TYPE_23__ {int NoBroadcastLimiter; } ;
struct TYPE_22__ {int L3SwitchMode; char* UserNameReal; int /*<<< orphan*/  ref; int /*<<< orphan*/ * Username; TYPE_5__* L3If; int /*<<< orphan*/ * Name; } ;
struct TYPE_21__ {int /*<<< orphan*/  Name; TYPE_11__* Cedar; } ;
struct TYPE_20__ {scalar_t__ ServerType; } ;
struct TYPE_19__ {int /*<<< orphan*/  SessionCounter; } ;
struct TYPE_18__ {TYPE_1__* Server; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_3__ SESSION ;
typedef  TYPE_4__ POLICY ;
typedef  TYPE_5__ L3IF ;
typedef  TYPE_6__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTION_HUB_LAYER3 ; 
 TYPE_4__* ClonePolicy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConvertSafeFileName (char*,int,char*) ; 
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDefaultPolicy () ; 
 int /*<<< orphan*/  GetMachineHostName (char*,int) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 char* L3_USERNAME ; 
 int MAX_SIZE ; 
 TYPE_6__* NewServerConnection (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* NewServerSession (TYPE_11__*,TYPE_6__*,TYPE_13__*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseConnection (TYPE_6__*) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  SessionMain (TYPE_3__*) ; 
 int /*<<< orphan*/  StrCat (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 

void L3IfThread(THREAD *t, void *param)
{
	L3IF *f;
	CONNECTION *c;
	SESSION *s;
	POLICY *policy;
	char tmp[MAX_SIZE];
	char name[MAX_SIZE];
	char username[MAX_SIZE];
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	f = (L3IF *)param;

	StrCpy(username, sizeof(username), L3_USERNAME);
	if (f->Switch != NULL)
	{
		StrCat(username, sizeof(username), f->Switch->Name);
	}

	// Create a connection
	c = NewServerConnection(f->Switch->Cedar, NULL, t);
	c->Protocol = CONNECTION_HUB_LAYER3;

	// Create a Session
	policy = ClonePolicy(GetDefaultPolicy());
	// Not to limit the number of broadcast by policy
	policy->NoBroadcastLimiter = true;
	s = NewServerSession(f->Switch->Cedar, c, f->Hub, username, policy);
	c->Session = s;

	ReleaseConnection(c);

	// Determine the name of the session
	GetMachineHostName(tmp, sizeof(tmp));
	if (f->Switch->Cedar->Server->ServerType == SERVER_TYPE_STANDALONE)
	{
		Format(name, sizeof(name), "SID-L3-%s-%u", f->Switch->Name, Inc(f->Hub->SessionCounter));
	}
	else
	{
		Format(name, sizeof(name), "SID-L3-%s-%s-%u", tmp, f->Switch->Name, Inc(f->Hub->SessionCounter));
	}
	ConvertSafeFileName(name, sizeof(name), name);
	StrUpper(name);

	Free(s->Name);
	s->Name = CopyStr(name);

	s->L3SwitchMode = true;
	s->L3If = f;

	if (s->Username != NULL)
	{
		Free(s->Username);
	}
	s->Username = CopyStr(username);

	StrCpy(s->UserNameReal, sizeof(s->UserNameReal), username);

	f->Session = s;
	AddRef(s->ref);

	// Notify the initialization completion
	NoticeThreadInit(t);

	// Session main process
	SessionMain(s);

	// Release the session
	ReleaseSession(s);
}