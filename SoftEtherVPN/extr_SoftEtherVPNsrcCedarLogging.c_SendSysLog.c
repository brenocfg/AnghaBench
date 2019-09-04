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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {scalar_t__ NextPollIp; scalar_t__ DestPort; int /*<<< orphan*/  lock; int /*<<< orphan*/  DestIp; int /*<<< orphan*/  Udp; int /*<<< orphan*/  HostName; } ;
typedef  TYPE_1__ SLOG ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int CalcUniToUtf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 scalar_t__ GetIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 scalar_t__ SYSLOG_POLL_IP_INTERVAL ; 
 scalar_t__ SYSLOG_POLL_IP_INTERVAL_NG ; 
 int /*<<< orphan*/  SendTo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UniToUtf8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

void SendSysLog(SLOG *g, wchar_t *str)
{
	UCHAR *buf;
	UINT buf_size;
	// Validate arguments
	if (g == NULL || str == NULL)
	{
		return;
	}

	buf_size = CalcUniToUtf8(str);
	buf = ZeroMalloc(buf_size);
	UniToUtf8(buf, buf_size, str);

	if (buf_size >= 1024)
	{
		buf_size = 1023;
	}

	Lock(g->lock);
	{
		if (Tick64() >= g->NextPollIp)
		{
			IP ip;

			if (GetIP(&ip, g->HostName))
			{
				g->NextPollIp = Tick64() + SYSLOG_POLL_IP_INTERVAL;
				Copy(&g->DestIp, &ip, sizeof(IP));
			}
			else
			{
				g->NextPollIp = Tick64() + SYSLOG_POLL_IP_INTERVAL_NG;
			}
		}

		if (g->DestPort != 0 && IsZeroIp(&g->DestIp) == false)
		{
			SendTo(g->Udp, &g->DestIp, g->DestPort, buf, buf_size);
		}
	}
	Unlock(g->lock);

	Free(buf);
}