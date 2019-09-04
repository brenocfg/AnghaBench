#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * IpWaitTable; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_11__ {scalar_t__ DestIP; struct TYPE_11__* Data; int /*<<< orphan*/  Size; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ IP_WAIT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VirtualIpSend (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

void SendWaitingIp(VH *v, UCHAR *mac, UINT dest_ip)
{
	UINT i;
	LIST *o = NULL;
	// Validate arguments
	if (v == NULL || mac == NULL)
	{
		return;
	}

	// Get a target list
	for (i = 0;i < LIST_NUM(v->IpWaitTable);i++)
	{
		IP_WAIT *w = LIST_DATA(v->IpWaitTable, i);

		if (w->DestIP == dest_ip)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}
			Add(o, w);
		}
	}

	// Send the target packets at once
	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			IP_WAIT *w = LIST_DATA(o, i);

			// Transmission processing
			VirtualIpSend(v, mac, w->Data, w->Size);

			// Remove from the list
			Delete(v->IpWaitTable, w);

			// Release the memory
			Free(w->Data);
			Free(w);
		}

		ReleaseList(o);
	}
}