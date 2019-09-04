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
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ GetIP4Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ GetIP6Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroIP4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroIP6 (int /*<<< orphan*/ *) ; 

bool GetIP46Ex(IP *ip4, IP *ip6, char *hostname, UINT timeout, bool *cancel)
{
	IP a, b;
	bool ok_a, ok_b;
	// Validate arguments
	if (ip4 == NULL || ip6 == NULL || hostname == NULL)
	{
		return false;
	}

	ZeroIP4(ip4);
	ZeroIP6(ip6);

	ok_a = ok_b = false;

	if (GetIP6Ex(&a, hostname, timeout, cancel))
	{
		ok_a = true;
	}

	if (GetIP4Ex(&b, hostname, timeout, cancel))
	{
		ok_b = true;
	}

	if (ok_a)
	{
		if (IsIP4(&a))
		{
			Copy(ip4, &a, sizeof(IP));
		}
	}
	if (ok_b)
	{
		if (IsIP4(&b))
		{
			Copy(ip4, &b, sizeof(IP));
		}

		if (IsIP6(&b))
		{
			Copy(ip6, &b, sizeof(IP));
		}
	}
	if (ok_a)
	{
		if (IsIP6(&a))
		{
			Copy(ip6, &a, sizeof(IP));
		}
	}

	if (IsZeroIp(ip4) && IsZeroIp(ip6))
	{
		return false;
	}

	return true;
}