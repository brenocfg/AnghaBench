#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int Now; int /*<<< orphan*/ * ArpWaitTable; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int GiveupTime; scalar_t__ TimeoutTime; int /*<<< orphan*/  IpAddress; scalar_t__ NextTimeoutTimeValue; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ ARP_WAIT ;

/* Variables and functions */
 scalar_t__ ARP_REQUEST_TIMEOUT ; 
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteArpWaitTable (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VirtualArpSendRequest (TYPE_1__*,int /*<<< orphan*/ ) ; 

void PollingArpWaitTable(VH *v)
{
	UINT i;
	LIST *o;
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	// Initialize the deletion list
	o = NULL;

	// Scan whole ARP waiting list
	for (i = 0;i < LIST_NUM(v->ArpWaitTable);i++)
	{
		ARP_WAIT *w = LIST_DATA(v->ArpWaitTable, i);

		if (w->GiveupTime < v->Now || (w->GiveupTime - 100 * 1000) > v->Now)
		{
			// Give up the sending of ARP
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}
			Add(o, w);
		}
		else
		{
			if (w->TimeoutTime < v->Now)
			{
				// Send an ARP again
				VirtualArpSendRequest(v, w->IpAddress);

				// Set the next timeout time
				w->TimeoutTime = v->Now + (UINT64)w->NextTimeoutTimeValue;
				// Increase the ARP transmission interval of the second and subsequent
				w->NextTimeoutTimeValue = w->NextTimeoutTimeValue + ARP_REQUEST_TIMEOUT;
			}
		}
	}

	// Remove if there is a ARP waiting record to be deleted
	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			ARP_WAIT *w = LIST_DATA(o, i);

			DeleteArpWaitTable(v, w->IpAddress);
		}
		ReleaseList(o);
	}
}