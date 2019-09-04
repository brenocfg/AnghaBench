#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* SockEvent; } ;
struct TYPE_6__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SOCK_EVENT ;
typedef  TYPE_2__ IKE_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (TYPE_1__*) ; 

void SetIKEServerSockEvent(IKE_SERVER *ike, SOCK_EVENT *e)
{
	// Validate arguments
	if (ike == NULL)
	{
		return;
	}

	if (e != NULL)
	{
		AddRef(e->ref);
	}

	if (ike->SockEvent != NULL)
	{
		ReleaseSockEvent(ike->SockEvent);
	}

	ike->SockEvent = e;
}