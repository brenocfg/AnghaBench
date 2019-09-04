#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_13__ {TYPE_2__* v; TYPE_1__* NatTableForSend; } ;
struct TYPE_12__ {scalar_t__ Status; scalar_t__ LastCommTime; scalar_t__ Protocol; } ;
struct TYPE_11__ {scalar_t__ Now; scalar_t__ NatUdpTimeout; scalar_t__ NatTcpTimeout; } ;
struct TYPE_10__ {int /*<<< orphan*/ * AllList; } ;
typedef  TYPE_3__ NATIVE_NAT_ENTRY ;
typedef  TYPE_4__ NATIVE_NAT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ NAT_TCP ; 
 scalar_t__ NAT_TCP_CONNECTED ; 
 scalar_t__ NAT_TCP_ESTABLISHED ; 
 scalar_t__ NN_TIMEOUT_FOR_UNESTBALISHED_TCP ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NnDeleteSession (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void NnDeleteOldSessions(NATIVE_NAT *t)
{
	UINT i;
	LIST *o;
	UINT64 now;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	o = NULL;
	now = t->v->Now;

	for (i = 0;i < LIST_NUM(t->NatTableForSend->AllList);i++)
	{
		NATIVE_NAT_ENTRY *e = LIST_DATA(t->NatTableForSend->AllList, i);
		UINT64 timeout;

		if (e->Status == NAT_TCP_CONNECTED || e->Status == NAT_TCP_ESTABLISHED)
		{
			timeout = e->LastCommTime + (UINT64)(e->Protocol == NAT_TCP ? t->v->NatTcpTimeout : t->v->NatUdpTimeout);
		}
		else
		{
			timeout = e->LastCommTime + (UINT64)NN_TIMEOUT_FOR_UNESTBALISHED_TCP;
		}

		if (timeout < now)
		{
			// Time-out occurs
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Add(o, e);
		}
	}

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			NATIVE_NAT_ENTRY *e = LIST_DATA(o, i);

			NnDeleteSession(t, e);
		}

		ReleaseList(o);
	}
}