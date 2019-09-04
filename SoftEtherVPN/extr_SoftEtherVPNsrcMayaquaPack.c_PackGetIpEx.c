#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  ipv6_scope_id; } ;
typedef  TYPE_1__ UCHAR ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,char*) ; 
 int /*<<< orphan*/ * GetElement (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IsBigEndian () ; 
 int MAX_PATH ; 
 scalar_t__ PackGetBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackGetDataEx2 (int /*<<< orphan*/ *,char*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetIP6 (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Swap32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINTToIP (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_INT ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool PackGetIpEx(PACK *p, char *name, IP *ip, UINT index)
{
	UINT i;
	char tmp[MAX_PATH];
	// Validate arguments
	if (p == NULL || ip == NULL || name == NULL)
	{
		return false;
	}

	Format(tmp, sizeof(tmp), "%s@ipv6_bool", name);
	if (PackGetBoolEx(p, tmp, index))
	{
		UCHAR data[16];
		UINT scope_id;

		Zero(data, sizeof(data));

		Format(tmp, sizeof(tmp), "%s@ipv6_array", name);
		PackGetDataEx2(p, tmp, data, sizeof(data), index);

		Format(tmp, sizeof(tmp), "%s@ipv6_scope_id", name);
		scope_id = PackGetIntEx(p, tmp, index);

		SetIP6(ip, data);
		ip->ipv6_scope_id = scope_id;
	}
	else
	{
		if (GetElement(p, name, VALUE_INT) == NULL)
		{
			Zero(ip, sizeof(IP));
			return false;
		}

		i = PackGetIntEx(p, name, index);

		if (IsBigEndian())
		{
			i = Swap32(i);
		}

		UINTToIP(ip, i);
	}

	return true;
}