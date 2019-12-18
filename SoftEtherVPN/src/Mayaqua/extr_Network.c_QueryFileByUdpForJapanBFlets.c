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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  char IP ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BFLETS_DNS_PROXY_TIMEOUT_FOR_GET_F ; 
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Clone (char*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 int IsIPv6LocalNetworkAddress (char*) ; 
 int IsZeroIp (char*) ; 
 char* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * QueryFileByIPv6Udp (int /*<<< orphan*/ *,scalar_t__,int*) ; 
 int /*<<< orphan*/ * ReadDump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int StartWith (char*,char*) ; 
 scalar_t__ StrToIP6 (char*,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  UDP_FILE_QUERY_BFLETS_TXT_FILENAME ; 

BUF *QueryFileByUdpForJapanBFlets(UINT timeout, bool *cancel)
{
	bool dummy_flag = false;
	BUF *txt_buf = NULL;
	BUF *ret = NULL;
	LIST *ip_list = NULL;
	UINT i;
	// Validate arguments
	if (cancel == NULL)
	{
		cancel = &dummy_flag;
	}
	if (timeout == 0)
	{
		timeout = BFLETS_DNS_PROXY_TIMEOUT_FOR_GET_F;
	}

	txt_buf = ReadDump(UDP_FILE_QUERY_BFLETS_TXT_FILENAME);
	if (txt_buf == NULL)
	{
		return NULL;
	}

	ip_list = NewListFast(NULL);

	while (true)
	{
		char *line = CfgReadNextLine(txt_buf);
		if (line == NULL)
		{
			break;
		}

		Trim(line);

		if (IsEmptyStr(line) == false && StartWith(line, "#") == false)
		{
			IP ip;

			if (StrToIP6(&ip, line))
			{
				if (IsZeroIp(&ip) == false)
				{
					if (IsIPv6LocalNetworkAddress(&ip) == false)
					{
						Add(ip_list, Clone(&ip, sizeof(IP)));
					}
				}
			}
		}

		Free(line);
	}

	FreeBuf(txt_buf);

	ret = QueryFileByIPv6Udp(ip_list, timeout, cancel);

	for (i = 0;i < LIST_NUM(ip_list);i++)
	{
		IP *ip = LIST_DATA(ip_list, i);

		Free(ip);
	}

	ReleaseList(ip_list);

	return ret;
}