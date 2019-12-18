#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  dummy ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {int JsonHint_IsArray; int JsonHint_IsIP; } ;
struct TYPE_9__ {int ipv6_scope_id; int /*<<< orphan*/ * ipv6_addr; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ IP ;
typedef  TYPE_2__ ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,char*) ; 
 int IPToUINT (TYPE_1__*) ; 
 scalar_t__ IsBigEndian () ; 
 int IsIP6 (TYPE_1__*) ; 
 int MAX_PATH ; 
 TYPE_2__* PackAddBoolEx (int /*<<< orphan*/ *,char*,int,int,int) ; 
 TYPE_2__* PackAddDataEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int) ; 
 TYPE_2__* PackAddIntEx (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int Swap32 (int) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void PackAddIpEx2(PACK *p, char *name, IP *ip, UINT index, UINT total, bool is_single)
{
	UINT i;
	bool b = false;
	char tmp[MAX_PATH];
	ELEMENT *e;
	// Validate arguments
	if (p == NULL || name == NULL || ip == NULL)
	{
		return;
	}
	if (total >= 2)
	{
		is_single = false;
	}

	b = IsIP6(ip);

	Format(tmp, sizeof(tmp), "%s@ipv6_bool", name);
	e = PackAddBoolEx(p, tmp, b, index, total);
	if (e != NULL && is_single) e->JsonHint_IsArray = false;
	if (e != NULL) e->JsonHint_IsIP = true;

	Format(tmp, sizeof(tmp), "%s@ipv6_array", name);
	if (b)
	{
		e = PackAddDataEx(p, tmp, ip->ipv6_addr, sizeof(ip->ipv6_addr), index, total);
		if (e != NULL && is_single) e->JsonHint_IsArray = false;
		if (e != NULL) e->JsonHint_IsIP = true;
	}
	else
	{
		UCHAR dummy[16];

		Zero(dummy, sizeof(dummy));

		e = PackAddDataEx(p, tmp, dummy, sizeof(dummy), index, total);
		if (e != NULL && is_single) e->JsonHint_IsArray = false;
		if (e != NULL) e->JsonHint_IsIP = true;
	}

	Format(tmp, sizeof(tmp), "%s@ipv6_scope_id", name);
	if (b)
	{
		e = PackAddIntEx(p, tmp, ip->ipv6_scope_id, index, total);
		if (e != NULL && is_single) e->JsonHint_IsArray = false;
		if (e != NULL) e->JsonHint_IsIP = true;
	}
	else
	{
		e = PackAddIntEx(p, tmp, 0, index, total);
		if (e != NULL && is_single) e->JsonHint_IsArray = false;
		if (e != NULL) e->JsonHint_IsIP = true;
	}

	i = IPToUINT(ip);

	if (IsBigEndian())
	{
		i = Swap32(i);
	}

	e = PackAddIntEx(p, name, i, index, total);
	if (e != NULL && is_single) e->JsonHint_IsArray = false;
	if (e != NULL) e->JsonHint_IsIP = true;
}