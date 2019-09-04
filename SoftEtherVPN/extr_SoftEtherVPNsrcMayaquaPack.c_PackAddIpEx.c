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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  dummy ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  ipv6_scope_id; int /*<<< orphan*/ * ipv6_addr; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,char*) ; 
 int /*<<< orphan*/  IPToUINT (TYPE_1__*) ; 
 scalar_t__ IsBigEndian () ; 
 int IsIP6 (TYPE_1__*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddDataEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Swap32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void PackAddIpEx(PACK *p, char *name, IP *ip, UINT index, UINT total)
{
	UINT i;
	bool b = false;
	char tmp[MAX_PATH];
	// Validate arguments
	if (p == NULL || name == NULL || ip == NULL)
	{
		return;
	}

	b = IsIP6(ip);

	Format(tmp, sizeof(tmp), "%s@ipv6_bool", name);
	PackAddBoolEx(p, tmp, b, index, total);

	Format(tmp, sizeof(tmp), "%s@ipv6_array", name);
	if (b)
	{
		PackAddDataEx(p, tmp, ip->ipv6_addr, sizeof(ip->ipv6_addr), index, total);
	}
	else
	{
		UCHAR dummy[16];

		Zero(dummy, sizeof(dummy));

		PackAddDataEx(p, tmp, dummy, sizeof(dummy), index, total);
	}

	Format(tmp, sizeof(tmp), "%s@ipv6_scope_id", name);
	if (b)
	{
		PackAddIntEx(p, tmp, ip->ipv6_scope_id, index, total);
	}
	else
	{
		PackAddIntEx(p, tmp, 0, index, total);
	}

	i = IPToUINT(ip);

	if (IsBigEndian())
	{
		i = Swap32(i);
	}

	PackAddIntEx(p, name, i, index, total);
}