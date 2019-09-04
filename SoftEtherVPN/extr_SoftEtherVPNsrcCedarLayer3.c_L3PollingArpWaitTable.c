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
typedef  scalar_t__ UINT ;
struct TYPE_10__ {scalar_t__ Expire; scalar_t__ LastSentTime; int /*<<< orphan*/  IpAddress; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ArpWaitTable; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ L3IF ;
typedef  TYPE_2__ L3ARPWAIT ;

/* Variables and functions */
 scalar_t__ ARP_REQUEST_TIMEOUT ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  L3SendArpRequestNow (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 

void L3PollingArpWaitTable(L3IF *f)
{
	UINT i;
	LIST *o = NULL;
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(f->ArpWaitTable);i++)
	{
		L3ARPWAIT *w = LIST_DATA(f->ArpWaitTable, i);

		if (w->Expire <= Tick64())
		{
			// The ARP request entry is expired
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Insert(o, w);
		}
		else if ((w->LastSentTime + ARP_REQUEST_TIMEOUT) <= Tick64())
		{
			// Send a next ARP request packet
			w->LastSentTime = Tick64();

			L3SendArpRequestNow(f, w->IpAddress);
		}
	}

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			L3ARPWAIT *w = LIST_DATA(o, i);

			Delete(f->ArpWaitTable, w);
			Free(w);
		}

		ReleaseList(o);
	}
}