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
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  DDNS_CLIENT ;

/* Variables and functions */
 scalar_t__ DCGetMyIpMain (int /*<<< orphan*/ *,int,char*,scalar_t__,int,char*) ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCurrentGlobalIP (int /*<<< orphan*/ *,int) ; 
 scalar_t__ StrToIP (int /*<<< orphan*/ *,char*) ; 

UINT DCGetMyIp(DDNS_CLIENT *c, bool ipv6, char *dst, UINT dst_size, char *replace_v6)
{
	UINT ret = ERR_INTERNAL_ERROR;

	ret = DCGetMyIpMain(c, ipv6, dst, dst_size, false, replace_v6);


	if (ret == ERR_NO_ERROR)
	{
		IP ip;

		if (StrToIP(&ip, dst))
		{
			if (ipv6 == false && IsIP4(&ip))
			{
				SetCurrentGlobalIP(&ip, false);
			}
			else if (ipv6 && IsIP6(&ip))
			{
				SetCurrentGlobalIP(&ip, true);
			}
		}
	}

	return ret;
}