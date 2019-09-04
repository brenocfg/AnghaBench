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
typedef  int /*<<< orphan*/  ip ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPToStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 int IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetIP6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void IPToStr4or6(char *str, UINT size, UINT ip_4_uint, UCHAR *ip_6_bytes)
{
	IP ip4;
	IP ip6;
	IP ip;
	// Validate arguments
	if (str == NULL)
	{
		return;
	}

	Zero(&ip, sizeof(ip));

	UINTToIP(&ip4, ip_4_uint);
	SetIP6(&ip6, ip_6_bytes);

	if (IsIP6(&ip4) || (IsZeroIp(&ip4) && (IsZeroIp(&ip6) == false)))
	{
		Copy(&ip, &ip6, sizeof(IP));
	}
	else
	{
		Copy(&ip, &ip4, sizeof(IP));
	}

	IPToStr(str, size, &ip);
}