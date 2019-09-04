#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  SockEvent; } ;
typedef  TYPE_1__ VH ;
struct TYPE_6__ {int DisconnectNow; } ;
typedef  TYPE_2__ NAT_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 

void DisconnectNatEntryNow(VH *v, NAT_ENTRY *e)
{
	// Validate arguments
	if (v == NULL || e == NULL)
	{
		return;
	}

	if (e->DisconnectNow == false)
	{
		e->DisconnectNow = true;

		SetSockEvent(v->SockEvent);
	}
}