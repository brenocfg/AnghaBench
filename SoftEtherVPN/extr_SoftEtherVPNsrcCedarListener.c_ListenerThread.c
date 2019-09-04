#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int Protocol; TYPE_1__* Thread; int /*<<< orphan*/  ref; } ;
struct TYPE_8__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ THREAD ;
typedef  TYPE_2__ LISTENER ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
#define  LISTENER_DNS 134 
#define  LISTENER_ICMP 133 
#define  LISTENER_INPROC 132 
#define  LISTENER_REVERSE 131 
#define  LISTENER_RUDP 130 
#define  LISTENER_TCP 129 
#define  LISTENER_UDP 128 
 int /*<<< orphan*/  ListenerTCPMainLoop (TYPE_2__*) ; 
 int /*<<< orphan*/  ListenerUDPMainLoop (TYPE_2__*) ; 
 int /*<<< orphan*/  NoticeThreadInit (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseListener (TYPE_2__*) ; 

void ListenerThread(THREAD *thread, void *param)
{
	LISTENER *r;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	// Initialize
	r = (LISTENER *)param;
	AddRef(r->ref);
	r->Thread = thread;
	AddRef(thread->ref);
	NoticeThreadInit(thread);

	// Main loop
	switch (r->Protocol)
	{
	case LISTENER_TCP:
	case LISTENER_INPROC:
	case LISTENER_RUDP:
	case LISTENER_DNS:
	case LISTENER_ICMP:
	case LISTENER_REVERSE:
		// TCP or other stream-based protocol
		ListenerTCPMainLoop(r);
		break;

	case LISTENER_UDP:
		// UDP protocol
		ListenerUDPMainLoop(r);
		break;
	}

	// Release
	ReleaseListener(r);
}