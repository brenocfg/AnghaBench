#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_17__ {int flag1; int /*<<< orphan*/  Name; int /*<<< orphan*/  ClientHostname; int /*<<< orphan*/  Cedar; } ;
struct TYPE_16__ {int /*<<< orphan*/  Cedar; int /*<<< orphan*/  Port; int /*<<< orphan*/  ref; } ;
struct TYPE_15__ {int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteIP; int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  ref; } ;
struct TYPE_14__ {TYPE_2__* s; TYPE_3__* r; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ TCP_ACCEPTED_PARAM ;
typedef  TYPE_2__ SOCK ;
typedef  TYPE_3__ LISTENER ;
typedef  TYPE_4__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  AcceptInit (TYPE_2__*) ; 
 int /*<<< orphan*/  AddConnection (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConnectionAccept (TYPE_4__*) ; 
 int /*<<< orphan*/  Debug (char*,char*,int) ; 
 int /*<<< orphan*/  Disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int IS_SPECIAL_PORT (int /*<<< orphan*/ ) ; 
 TYPE_4__* NewServerConnection (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseConnection (TYPE_4__*) ; 
 int /*<<< orphan*/  ReleaseListener (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_2__*) ; 
 int /*<<< orphan*/  SLog (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void TCPAcceptedThread(THREAD *t, void *param)
{
	TCP_ACCEPTED_PARAM *data;
	LISTENER *r;
	SOCK *s;
	CONNECTION *c;
	bool flag1;
	char tmp[128];
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	// Initialize
	data = (TCP_ACCEPTED_PARAM *)param;
	r = data->r;
	s = data->s;
	AddRef(r->ref);
	AddRef(s->ref);

	// Create a connection
	c = NewServerConnection(r->Cedar, s, t);

	// Register to Cedar as a transient connection
	AddConnection(c->Cedar, c);

	NoticeThreadInit(t);

	AcceptInit(s);
	StrCpy(c->ClientHostname, sizeof(c->ClientHostname), s->RemoteHostname);
	IPToStr(tmp, sizeof(tmp), &s->RemoteIP);
	if (IS_SPECIAL_PORT(s->RemotePort) == false)
	{
		SLog(r->Cedar, "LS_LISTENER_ACCEPT", r->Port, tmp, s->RemoteHostname, s->RemotePort);
	}

	// Reception
	ConnectionAccept(c);
	flag1 = c->flag1;

	// Release
	SLog(r->Cedar, "LS_CONNECTION_END_1", c->Name);
	ReleaseConnection(c);

	// Release
	if (flag1 == false)
	{
		Debug("%s %u flag1 == false\n", __FILE__, __LINE__);
		IPToStr(tmp, sizeof(tmp), &s->RemoteIP);

		if (IS_SPECIAL_PORT(s->RemotePort) == false)
		{
			SLog(r->Cedar, "LS_LISTENER_DISCONNECT", tmp, s->RemotePort);
		}
		Disconnect(s);
	}
	ReleaseSock(s);
	ReleaseListener(r);
}