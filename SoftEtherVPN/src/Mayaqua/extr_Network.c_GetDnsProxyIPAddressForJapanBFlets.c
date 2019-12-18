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
struct TYPE_3__ {char* Value; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ INI_ENTRY ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 scalar_t__ BFLETS_DNS_PROXY_TIMEOUT_FOR_GET_F ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeIni (int /*<<< orphan*/ *) ; 
 TYPE_1__* GetIniEntry (int /*<<< orphan*/ *,char*) ; 
 int IsEmptyStr (char*) ; 
 int IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * QueryFileByUdpForJapanBFlets (scalar_t__,int*) ; 
 int /*<<< orphan*/ * ReadIni (int /*<<< orphan*/ *) ; 
 scalar_t__ StrToIP (int /*<<< orphan*/ *,char*) ; 

bool GetDnsProxyIPAddressForJapanBFlets(IP *ip_ret, UINT timeout, bool *cancel)
{
	BUF *b;
	LIST *o;
	bool ret = false;
	// Validate arguments
	if (ip_ret == NULL)
	{
		return false;
	}
	if (timeout == 0)
	{
		timeout = BFLETS_DNS_PROXY_TIMEOUT_FOR_GET_F;
	}

	b = QueryFileByUdpForJapanBFlets(timeout, cancel);

	if (b == NULL)
	{
		return false;
	}

	o = ReadIni(b);

	if (o != NULL)
	{
		INI_ENTRY *e = GetIniEntry(o, "DDnsServerForBFlets");

		if (e != NULL)
		{
			char *s = e->Value;

			if (IsEmptyStr(s) == false)
			{
				IP ip;

				if (StrToIP(&ip, s))
				{
					if (IsZeroIp(&ip) == false)
					{
						Copy(ip_ret, &ip, sizeof(IP));
						ret = true;
					}
				}
			}
		}
	}

	FreeIni(o);
	FreeBuf(b);

	return ret;
}