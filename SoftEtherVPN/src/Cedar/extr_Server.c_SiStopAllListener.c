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
struct TYPE_10__ {int /*<<< orphan*/ * DynListenerDns; int /*<<< orphan*/ * DynListenerIcmp; int /*<<< orphan*/ * ServerListenerList; } ;
struct TYPE_9__ {int /*<<< orphan*/  Port; } ;
typedef  TYPE_1__ SERVER_LISTENER ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FreeDynamicListener (int /*<<< orphan*/ *) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiDeleteListener (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiLockListenerList (TYPE_2__*) ; 
 int /*<<< orphan*/  SiUnlockListenerList (TYPE_2__*) ; 

void SiStopAllListener(SERVER *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	SiLockListenerList(s);
	{
		UINT i;
		LIST *o = NewListFast(NULL);
		for (i = 0;i < LIST_NUM(s->ServerListenerList);i++)
		{
			SERVER_LISTENER *e = LIST_DATA(s->ServerListenerList, i);
			Add(o, e);
		}

		for (i = 0;i < LIST_NUM(o);i++)
		{
			SERVER_LISTENER *e = LIST_DATA(o, i);
			SiDeleteListener(s, e->Port);
		}

		ReleaseList(o);
	}
	SiUnlockListenerList(s);

	ReleaseList(s->ServerListenerList);

	// Stop the VPN over ICMP listener
	FreeDynamicListener(s->DynListenerIcmp);
	s->DynListenerIcmp = NULL;

	// Stop the VPN over DNS listener
	FreeDynamicListener(s->DynListenerDns);
	s->DynListenerDns = NULL;
}