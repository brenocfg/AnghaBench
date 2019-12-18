#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* SendQueue; void* IpWaitList; void* IpPacketQueue; void* ArpWaitTable; void* ArpTable; } ;
typedef  TYPE_1__ L3IF ;

/* Variables and functions */
 int /*<<< orphan*/ * CmpL3ArpEntry ; 
 int /*<<< orphan*/ * CmpL3ArpWaitTable ; 
 int /*<<< orphan*/  L3GenerateMacAddress (TYPE_1__*) ; 
 void* NewList (int /*<<< orphan*/ *) ; 
 void* NewQueue () ; 

void L3InitInterface(L3IF *f)
{
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	// MAC address generation
	L3GenerateMacAddress(f);

	// List generation
	f->ArpTable = NewList(CmpL3ArpEntry);
	f->ArpWaitTable = NewList(CmpL3ArpWaitTable);
	f->IpPacketQueue = NewQueue();
	f->IpWaitList = NewList(NULL);
	f->SendQueue = NewQueue();
}