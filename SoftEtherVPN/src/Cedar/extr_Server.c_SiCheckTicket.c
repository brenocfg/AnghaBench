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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  TicketList; } ;
struct TYPE_7__ {int /*<<< orphan*/  Policy; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  UsernameReal; int /*<<< orphan*/  Username; int /*<<< orphan*/  Ticket; } ;
typedef  TYPE_1__ TICKET ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool SiCheckTicket(HUB *h, UCHAR *ticket, char *username, UINT username_size, char *usernamereal, UINT usernamereal_size, POLICY *policy, char *sessionname, UINT sessionname_size, char *groupname, UINT groupname_size)
{
	bool ret = false;
	// Validate arguments
	if (h == NULL || ticket == NULL || username == NULL || usernamereal == NULL || policy == NULL || sessionname == NULL)
	{
		return false;
	}

	LockList(h->TicketList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(h->TicketList);i++)
		{
			TICKET *t = LIST_DATA(h->TicketList, i);
			if (Cmp(t->Ticket, ticket, SHA1_SIZE) == 0)
			{
				ret = true;
				StrCpy(username, username_size, t->Username);
				StrCpy(usernamereal, usernamereal_size, t->UsernameReal);
				StrCpy(sessionname, sessionname_size, t->SessionName);
				StrCpy(groupname, groupname_size, t->GroupName);
				Copy(policy, &t->Policy, sizeof(POLICY));
				Delete(h->TicketList, t);
				Free(t);
				break;
			}
		}
	}
	UnlockList(h->TicketList);

	return ret;
}