#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  NextPollIp; int /*<<< orphan*/  HostName; scalar_t__ DestPort; int /*<<< orphan*/  DestIp; } ;
typedef  TYPE_1__ SLOG ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetIP (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSLOG_POLL_IP_INTERVAL ; 
 int /*<<< orphan*/  SYSLOG_POLL_IP_INTERVAL_NG ; 
 scalar_t__ SYSLOG_PORT ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void SetSysLog(SLOG *g, char *hostname, UINT port)
{
	IP ip;
	// Validate arguments
	if (g == NULL)
	{
		return;
	}
	if (port == 0)
	{
		port = SYSLOG_PORT;
	}

	if (hostname == NULL)
	{
		hostname = "";
	}

	Zero(&ip, sizeof(IP));
	GetIP(&ip, hostname);

	Lock(g->lock);
	{
		Copy(&g->DestIp, &ip, sizeof(IP));
		g->DestPort = port;
		StrCpy(g->HostName, sizeof(g->HostName), hostname);
		g->NextPollIp = Tick64() + IsZeroIp(&ip) ? SYSLOG_POLL_IP_INTERVAL_NG : SYSLOG_POLL_IP_INTERVAL;
	}
	Unlock(g->lock);
}