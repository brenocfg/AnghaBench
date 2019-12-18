#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_12__ {int DisableIPv6Listener; int /*<<< orphan*/  ref; } ;
struct TYPE_11__ {int LocalOnly; int ShadowIPv6; scalar_t__ volatile* NatTGlobalUdpPort; int EnableConditionalAccept; int /*<<< orphan*/  ShadowListener; TYPE_2__* Cedar; int /*<<< orphan*/  RandPortId; int /*<<< orphan*/  Event; scalar_t__ Port; scalar_t__ Protocol; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; void* ThreadParam; int /*<<< orphan*/ * ThreadProc; } ;
typedef  int /*<<< orphan*/  THREAD_PROC ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ LISTENER ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddListener (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 scalar_t__ LISTENER_DNS ; 
 scalar_t__ LISTENER_ICMP ; 
 scalar_t__ LISTENER_INPROC ; 
 scalar_t__ LISTENER_REVERSE ; 
 scalar_t__ LISTENER_RUDP ; 
 scalar_t__ LISTENER_TCP ; 
 int /*<<< orphan*/  ListenerThread ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewListenerEx3 (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,void*,int,int) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLog (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

LISTENER *NewListenerEx5(CEDAR *cedar, UINT proto, UINT port, THREAD_PROC *proc, void *thread_param, bool local_only, bool shadow_ipv6,
						 volatile UINT *natt_global_udp_port, UCHAR rand_port_id, bool enable_ca)
{
	LISTENER *r;
	THREAD *t;
	// Validate arguments
	if ((proto == LISTENER_TCP && port == 0) || cedar == NULL)
	{
		return NULL;
	}
	// Check the protocol number
	if (proto != LISTENER_TCP && proto != LISTENER_INPROC &&
		proto != LISTENER_RUDP && proto != LISTENER_ICMP && proto != LISTENER_DNS &&
		proto != LISTENER_REVERSE)
	{
		return NULL;
	}

	r = ZeroMalloc(sizeof(LISTENER));

	r->ThreadProc = proc;
	r->ThreadParam = thread_param;
	r->Cedar = cedar;
	AddRef(r->Cedar->ref);
	r->lock = NewLock();
	r->ref = NewRef();
	r->Protocol = proto;
	r->Port = port;
	r->Event = NewEvent();


	r->LocalOnly = local_only;
	r->ShadowIPv6 = shadow_ipv6;
	r->NatTGlobalUdpPort = natt_global_udp_port;
	r->RandPortId = rand_port_id;
	r->EnableConditionalAccept = enable_ca;

	if (r->ShadowIPv6 == false)
	{
		if (proto == LISTENER_TCP)
		{
			SLog(cedar, "LS_LISTENER_START_1", port);
		}
	}

	// Creating a thread
	t = NewThread(ListenerThread, r);
	WaitThreadInit(t);
	ReleaseThread(t);

	if (r->ShadowIPv6 == false && proto == LISTENER_TCP)
	{
		if (r->Cedar->DisableIPv6Listener == false)
		{
			// Add a shadow listener
			r->ShadowListener = NewListenerEx3(cedar, proto, port, proc, thread_param,
				local_only, true);
		}
	}

	if (r->ShadowIPv6 == false)
	{
		// Add to the Cedar
		AddListener(cedar, r);
	}

	return r;
}