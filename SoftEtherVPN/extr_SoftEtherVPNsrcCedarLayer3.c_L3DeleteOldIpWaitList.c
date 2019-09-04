#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_11__ {TYPE_1__* PacketData; } ;
struct TYPE_10__ {int /*<<< orphan*/ * IpWaitList; } ;
struct TYPE_9__ {scalar_t__ Expire; TYPE_6__* Packet; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ L3PACKET ;
typedef  TYPE_2__ L3IF ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreePacket (TYPE_6__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 

void L3DeleteOldIpWaitList(L3IF *f)
{
	UINT i;
	LIST *o = NULL;
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(f->IpWaitList);i++)
	{
		L3PACKET *p = LIST_DATA(f->IpWaitList, i);

		if (p->Expire <= Tick64())
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Insert(o, p);
		}
	}

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			L3PACKET *p = LIST_DATA(o, i);

			Delete(f->IpWaitList, p);

			Free(p->Packet->PacketData);
			FreePacket(p->Packet);
			Free(p);
		}

		ReleaseList(o);
	}
}