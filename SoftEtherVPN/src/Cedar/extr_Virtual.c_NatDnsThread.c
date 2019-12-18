#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {int DnsOk; int DnsGetIpFromHost; int DnsFinished; TYPE_1__* v; int /*<<< orphan*/  DnsResponseHostName; int /*<<< orphan*/  DnsTargetHostName; int /*<<< orphan*/  DnsResponseIp; } ;
struct TYPE_3__ {int /*<<< orphan*/  SockEvent; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 scalar_t__ ArpaToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int EndWith (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GetHostName (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NatGetIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 

void NatDnsThread(THREAD *t, void *param)
{
	NAT_ENTRY *n;
	IP ip;
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}
	n = (NAT_ENTRY *)param;

	// Notify the initialization completion
	NoticeThreadInit(t);

	// Run processing
	if (EndWith(n->DnsTargetHostName, ".in-addr.arpa") == false)
	{
		// Forward resolution
		if (NatGetIP(&ip, n->DnsTargetHostName))
		{
			// Forward resolution success
			Copy(&n->DnsResponseIp, &ip, sizeof(IP));
			n->DnsOk = true;
		}
	}
	else
	{
		// Reverse resolution
		IP ip;
		n->DnsGetIpFromHost = true;		// Set the reverse resolution flag
		// Convert a *.in-addr.arpa string to an IP address
		if (ArpaToIP(&ip, n->DnsTargetHostName))
		{
			// Reverse resolution process
			char tmp[256];
			if (GetHostName(tmp, sizeof(tmp), &ip))
			{
				// Reverse resolution success
				n->DnsResponseHostName = CopyStr(tmp);
				n->DnsOk = true;
			}
		}
	}

	// Notify the results
	n->DnsFinished = true;

	SetSockEvent(n->v->SockEvent);
}