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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int /*<<< orphan*/  AcceptingSockets; } ;
struct TYPE_12__ {scalar_t__ ThreadProc; TYPE_4__* Cedar; } ;
struct TYPE_11__ {int /*<<< orphan*/  RemoteIP; } ;
struct TYPE_10__ {TYPE_2__* s; TYPE_3__* r; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ TCP_ACCEPTED_PARAM ;
typedef  TYPE_2__ SOCK ;
typedef  TYPE_3__ LISTENER ;
typedef  TYPE_4__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  GetNumIpClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewThread (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 scalar_t__ TCPAcceptedThread ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void TCPAccepted(LISTENER *r, SOCK *s)
{
	TCP_ACCEPTED_PARAM *data;
	THREAD *t;
	char tmp[MAX_SIZE];
	UINT num_clients_from_this_ip = 0;
	CEDAR *cedar;
	// Validate arguments
	if (r == NULL || s == NULL)
	{
		return;
	}

	cedar = r->Cedar;

	num_clients_from_this_ip = GetNumIpClient(&s->RemoteIP);


	IPToStr(tmp, sizeof(tmp), &s->RemoteIP);

	data = ZeroMalloc(sizeof(TCP_ACCEPTED_PARAM));
	data->r = r;
	data->s = s;

	if (r->ThreadProc == TCPAcceptedThread)
	{
		Inc(cedar->AcceptingSockets);
	}

	t = NewThread(r->ThreadProc, data);
	WaitThreadInit(t);
	Free(data);
	ReleaseThread(t);
}