#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  username ;
typedef  int /*<<< orphan*/  ticket_str ;
typedef  int /*<<< orphan*/  sessionname ;
typedef  int /*<<< orphan*/  realusername ;
typedef  int /*<<< orphan*/  hubname ;
typedef  int /*<<< orphan*/  groupname ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_15__ {int /*<<< orphan*/ * TicketList; } ;
struct TYPE_14__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_13__ {scalar_t__ CreatedTick; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  UsernameReal; int /*<<< orphan*/  Username; int /*<<< orphan*/ * Ticket; int /*<<< orphan*/  Policy; } ;
typedef  TYPE_1__ TICKET ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_3__* GetHub (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  InRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_SESSION_NAME_LEN ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackGetData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int PackGetDataSize (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SLog (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  SiGetPoint (TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int TICKET_EXPIRES ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

PACK *SiCalledCreateTicket(SERVER *s, PACK *p)
{
	char username[MAX_SIZE];
	char hubname[MAX_SIZE];
	char groupname[MAX_SIZE];
	char realusername[MAX_SIZE];
	char sessionname[MAX_SESSION_NAME_LEN + 1];
	POLICY policy;
	UCHAR ticket[SHA1_SIZE];
	char ticket_str[MAX_SIZE];
	HUB *h;
	UINT i;
	PACK *ret;
	TICKET *t;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return NewPack();
	}

	PackGetStr(p, "UserName", username, sizeof(username));
	PackGetStr(p, "GroupName", groupname, sizeof(groupname));
	PackGetStr(p, "HubName", hubname, sizeof(hubname));
	PackGetStr(p, "RealUserName", realusername, sizeof(realusername));
	PackGetStr(p, "SessionName", sessionname, sizeof(sessionname));

	InRpcPolicy(&policy, p);
	if (PackGetDataSize(p, "Ticket") == SHA1_SIZE)
	{
		PackGetData(p, "Ticket", ticket);
	}

	BinToStr(ticket_str, sizeof(ticket_str), ticket, SHA1_SIZE);

	SLog(s->Cedar, "LS_TICKET_2", hubname, username, realusername, sessionname,
		ticket_str, TICKET_EXPIRES / 1000);

	// Get the HUB
	h = GetHub(s->Cedar, hubname);
	if (h == NULL)
	{
		return NewPack();
	}

	LockList(h->TicketList);
	{
		LIST *o = NewListFast(NULL);
		// Discard old tickets
		for (i = 0;i < LIST_NUM(h->TicketList);i++)
		{
			TICKET *t = LIST_DATA(h->TicketList, i);
			if ((t->CreatedTick + TICKET_EXPIRES) < Tick64())
			{
				Add(o, t);
			}
		}
		for (i = 0;i < LIST_NUM(o);i++)
		{
			TICKET *t = LIST_DATA(o, i);
			Delete(h->TicketList, t);
			Free(t);
		}
		ReleaseList(o);

		// Create a ticket
		t = ZeroMalloc(sizeof(TICKET));
		t->CreatedTick = Tick64();
		Copy(&t->Policy, &policy, sizeof(POLICY));
		Copy(t->Ticket, ticket, SHA1_SIZE);
		StrCpy(t->Username, sizeof(t->Username), username);
		StrCpy(t->UsernameReal, sizeof(t->UsernameReal), realusername);
		StrCpy(t->GroupName, sizeof(t->GroupName), groupname);
		StrCpy(t->SessionName, sizeof(t->SessionName), sessionname);

		Add(h->TicketList, t);
	}
	UnlockList(h->TicketList);

	ReleaseHub(h);

	ret = NewPack();

	PackAddInt(ret, "Point", SiGetPoint(s));

	return ret;
}