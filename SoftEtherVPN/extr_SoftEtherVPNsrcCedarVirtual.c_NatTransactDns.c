#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int NatDoCancelFlag; int /*<<< orphan*/  NatTable; } ;
typedef  TYPE_1__ VH ;
struct TYPE_8__ {int DnsFinished; int /*<<< orphan*/  lock; struct TYPE_8__* DnsResponseHostName; struct TYPE_8__* DnsTargetHostName; int /*<<< orphan*/ * DnsThread; scalar_t__ DisconnectNow; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ NAT_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  NatDnsThread ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 

bool NatTransactDns(VH *v, NAT_ENTRY *n)
{
	// Validate arguments
	if (v == NULL || n == NULL)
	{
		return true;
	}

	if (n->DisconnectNow)
	{
		goto DISCONNECT;
	}

	if (n->DnsThread == NULL && n->DnsFinished == false)
	{
		// Create a thread
		THREAD *t = NewThread(NatDnsThread, (void *)n);
		WaitThreadInit(t);
		n->DnsThread = t;
	}
	else
	{
		// Wait for the result
		if (n->DnsFinished)
		{
			// Results have been received
			WaitThread(n->DnsThread, INFINITE);
			ReleaseThread(n->DnsThread);
			n->DnsThread = NULL;
			// Notify to the main thread
			v->NatDoCancelFlag = true;
		}
	}

	return true;

DISCONNECT:

	// Releasing process
	if (n->DnsThread != NULL)
	{
		WaitThread(n->DnsThread, INFINITE);
		ReleaseThread(n->DnsThread);
		n->DnsThread = NULL;
	}

	if (n->DnsTargetHostName != NULL)
	{
		Free(n->DnsTargetHostName);
		n->DnsTargetHostName = NULL;
	}

	if (n->DnsResponseHostName != NULL)
	{
		Free(n->DnsResponseHostName);
		n->DnsResponseHostName = NULL;
	}

	DeleteLock(n->lock);
	Delete(v->NatTable, n);
	Free(n);

	return false;
}