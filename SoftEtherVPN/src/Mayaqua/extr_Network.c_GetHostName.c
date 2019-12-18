#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AddHostCache (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int GetHostCache (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetHostNameThread ; 
 int GetNetBiosName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TIMEOUT_HOSTNAME ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

bool GetHostName(char *hostname, UINT size, IP *ip)
{
	THREAD *t;
	IP *p_ip;
	bool ret;
	// Validate arguments
	if (hostname == NULL || ip == NULL)
	{
		return false;
	}

	if (GetHostCache(hostname, size, ip))
	{
		if (IsEmptyStr(hostname) == false)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	p_ip = ZeroMalloc(sizeof(IP));
	Copy(p_ip, ip, sizeof(IP));

	t = NewThread(GetHostNameThread, p_ip);

	WaitThreadInit(t);

	WaitThread(t, TIMEOUT_HOSTNAME);

	ReleaseThread(t);

	ret = GetHostCache(hostname, size, ip);
	if (ret == false)
	{
		if (IsIP4(ip))
		{
			ret = GetNetBiosName(hostname, size, ip);
			if (ret)
			{
				AddHostCache(ip, hostname);
			}
		}
	}
	else
	{
		if (IsEmptyStr(hostname))
		{
			ret = false;
		}
	}
	if (ret == false)
	{
		AddHostCache(ip, "");
		StrCpy(hostname, size, "");
	}

	return ret;
}