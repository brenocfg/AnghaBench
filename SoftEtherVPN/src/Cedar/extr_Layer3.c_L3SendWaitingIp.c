#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_13__ {TYPE_1__* PacketData; } ;
struct TYPE_12__ {int /*<<< orphan*/ * IpWaitList; } ;
struct TYPE_11__ {scalar_t__ NextHopIp; TYPE_7__* Packet; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ L3PACKET ;
typedef  TYPE_2__ L3IF ;
typedef  int /*<<< orphan*/  L3ARPENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreePacket (TYPE_7__*) ; 
 int /*<<< orphan*/  L3SendIpNow (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void L3SendWaitingIp(L3IF *f, UCHAR *mac, UINT ip, L3ARPENTRY *a)
{
	UINT i;
	LIST *o = NULL;
	// Validate arguments
	if (f == NULL || mac == NULL || a == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(f->IpWaitList);i++)
	{
		L3PACKET *p = LIST_DATA(f->IpWaitList, i);

		if (p->NextHopIp == ip)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}
			Add(o, p);
		}
	}

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			L3PACKET *p = LIST_DATA(o, i);

			// Transmission
			L3SendIpNow(f, a, p);

			Delete(f->IpWaitList, p);
			Free(p->Packet->PacketData);
			FreePacket(p->Packet);
			Free(p);
		}

		ReleaseList(o);
	}
}