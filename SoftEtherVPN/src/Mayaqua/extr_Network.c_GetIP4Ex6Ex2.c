#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hostname ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {char* HostName; int IPv6; int Ok; int /*<<< orphan*/  Ip; scalar_t__ Timeout; int /*<<< orphan*/  Ref; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ GETIP_THREAD_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,scalar_t__,...) ; 
 scalar_t__ DetectFletsType () ; 
 scalar_t__ FLETS_DETECT_TYPE_EAST_BFLETS_PRIVATE ; 
 scalar_t__ FLETS_DETECT_TYPE_EAST_NGN_PRIVATE ; 
 scalar_t__ FLETS_DETECT_TYPE_WEST_NGN_PRIVATE ; 
 int /*<<< orphan*/ * FLETS_NGN_EAST_DNS_PROXY_HOSTNAME ; 
 int /*<<< orphan*/ * FLETS_NGN_WEST_DNS_PROXY_HOSTNAME ; 
 scalar_t__ GetCurrentGetIpThreadNum () ; 
 scalar_t__ GetGetIpThreadMaxNum () ; 
 int /*<<< orphan*/  GetIP4Ex6ExThread ; 
 scalar_t__ GetIPViaDnsProxyForJapanFlets (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsUseDnsProxy () ; 
 int IsZeroIp (int /*<<< orphan*/ *) ; 
 scalar_t__ MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ QueryDnsCache (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReleaseGetIPThreadParam (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 scalar_t__ SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SleepThread (scalar_t__) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ StrToIP (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ TIMEOUT_GETIP ; 
 scalar_t__ Tick64 () ; 
 scalar_t__ WaitThread (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  getip_thread_counter ; 

bool GetIP4Ex6Ex2(IP *ip, char *hostname_arg, UINT timeout, bool ipv6, bool *cancel, bool only_direct_dns)
{
	GETIP_THREAD_PARAM *p;
	THREAD *t;
	bool ret = false;
	UINT64 start_tick = 0;
	UINT64 end_tick = 0;
	UINT64 spent_time = 0;
	UINT64 now;
	UINT n;
	bool use_dns_proxy = false;
	char hostname[260];
	UINT i;
	bool timed_out;
	// Validate arguments
	if (ip == NULL || hostname_arg == NULL)
	{
		return false;
	}
	if (timeout == 0)
	{
		timeout = TIMEOUT_GETIP;
	}

	Zero(hostname, sizeof(hostname));
	StrCpy(hostname, sizeof(hostname), hostname_arg);

	i = SearchStrEx(hostname, "/", 0, true);
	if (i != INFINITE)
	{
		hostname[i] = 0;
	}

	if (ipv6 == false)
	{
		IP ip2;

		if (StrToIP(&ip2, hostname) && IsZeroIp(&ip2) == false)
		{
			if (IsIP4(&ip2))
			{
				// IPv4 address direct specification
				Copy(ip, &ip2, sizeof(IP));
				return true;
			}
			else
			{
				// IPv6 address direct specification
				return false;
			}
		}
	}
	else
	{
		IP ip2;

		if (StrToIP(&ip2, hostname) && IsZeroIp(&ip2) == false)
		{
			if (IsIP6(&ip2))
			{
				// IPv6 address direct specification
				Copy(ip, &ip2, sizeof(IP));
				return true;
			}
			else
			{
				// IPv4 address direct specification
				return false;
			}
		}
	}

	if (only_direct_dns == false)
	{
		if (ipv6 == false)
		{
			if (IsUseDnsProxy())
			{
				use_dns_proxy = true;
			}
		}
	}


	// check the quota
	start_tick = Tick64();
	end_tick = start_tick + (UINT64)timeout;

	n = 0;

	timed_out = false;

	while (true)
	{
		UINT64 now = Tick64();
		UINT64 remain;
		UINT remain32;

		if (GetGetIpThreadMaxNum() > GetCurrentGetIpThreadNum())
		{
			// below the quota
			break;
		}

		if (now >= end_tick)
		{
			// timeouted
			timed_out = true;
			break;
		}

		if (cancel != NULL && (*cancel))
		{
			// cancelled
			timed_out = true;
			break;
		}

		remain = end_tick - now;
		remain32 = MIN((UINT)remain, 100);

		SleepThread(remain32);
		n++;
	}

	now = Tick64();
	spent_time = now - start_tick;

	if (n == 0)
	{
		spent_time = 0;
	}

	if ((UINT)spent_time >= timeout)
	{
		timed_out = true;
	}

	if (timed_out)
	{
		IP ip2;

		// timed out, cancelled
		if (QueryDnsCache(&ip2, hostname))
		{
			ret = true;

			Copy(ip, &ip2, sizeof(IP));
		}

		Debug("GetIP4Ex6Ex2: Worker thread quota exceeded: max=%u current=%u\n",
			GetGetIpThreadMaxNum(), GetCurrentGetIpThreadNum());

		return ret;
	}

	// Increment the counter
	Inc(getip_thread_counter);

	if (spent_time != 0)
	{
		Debug("GetIP4Ex6Ex2: Waited for %u msecs to create a worker thread.\n",
			spent_time);
	}

	timeout -= (UINT)spent_time;

	p = ZeroMalloc(sizeof(GETIP_THREAD_PARAM));
	p->Ref = NewRef();
	StrCpy(p->HostName, sizeof(p->HostName), hostname);
	p->IPv6 = ipv6;
	p->Timeout = timeout;
	p->Ok = false;

	t = NewThread(GetIP4Ex6ExThread, p);
	WaitThreadInit(t);

	if (cancel == NULL)
	{
		WaitThread(t, timeout);
	}
	else
	{
		start_tick = Tick64();
		end_tick = start_tick + (UINT64)timeout;

		while (true)
		{
			UINT64 now = Tick64();
			UINT64 remain;
			UINT remain32;

			if (*cancel)
			{
				break;
			}

			if (now >= end_tick)
			{
				break;
			}

			remain = end_tick - now;
			remain32 = MIN((UINT)remain, 100);

			if (WaitThread(t, remain32))
			{
				break;
			}
		}
	}

	ReleaseThread(t);

	if (p->Ok)
	{
		ret = true;
		Copy(ip, &p->Ip, sizeof(IP));
	}
	else
	{
		IP ip2;

#if	0
		if (only_direct_dns == false)
		{
			if (ipv6)
			{
				UINT flets_type = DetectFletsType();

				// if I'm in the FLETs of NTT East,
				// try to get an IP address using the DNS proxy server
				if ((flets_type & FLETS_DETECT_TYPE_EAST_BFLETS_PRIVATE) &&
					GetIPViaDnsProxyForJapanFlets(ip, hostname, true, 0, cancel, NULL))
				{
					// B FLETs
					ret = true;
				}
				else if ((flets_type & FLETS_DETECT_TYPE_EAST_NGN_PRIVATE) &&
					GetIPViaDnsProxyForJapanFlets(ip, hostname, true, 0, cancel, FLETS_NGN_EAST_DNS_PROXY_HOSTNAME))
				{
					// FLET'S Hikar-Next (NTT East)
					ret = true;
				}
				else if ((flets_type & FLETS_DETECT_TYPE_WEST_NGN_PRIVATE) &&
					GetIPViaDnsProxyForJapanFlets(ip, hostname, true, 0, cancel, FLETS_NGN_WEST_DNS_PROXY_HOSTNAME))
				{
					// FLET'S Hikar-Next (NTT West)
					ret = true;
				}
			}
		}
#endif

		if (QueryDnsCache(&ip2, hostname))
		{
			ret = true;

			Copy(ip, &ip2, sizeof(IP));
		}
	}


	ReleaseGetIPThreadParam(p);

	return ret;
}