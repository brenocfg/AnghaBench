#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ UNIX_VLAN ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  UnixVLanList; } ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 scalar_t__ LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool CiIsVLan(CLIENT *c, char *name)
{
	// Validate arguments
	if (c == NULL || name == NULL)
	{
		return false;
	}

#ifdef	OS_WIN32
	{
		TOKEN_LIST *t;
		UINT i;

		t = MsEnumNetworkAdapters(VLAN_ADAPTER_NAME, VLAN_ADAPTER_NAME_OLD);
		if (t == NULL)
		{
			return false;
		}

		for (i = 0;i < t->NumTokens;i++)
		{
			if (StrCmpi(t->Token[i], name) == 0)
			{
				FreeToken(t);
				return true;
			}
		}

		FreeToken(t);

		return false;
	}
#else	// OS_WIN32
	{
		UNIX_VLAN *v;
		UINT i;
		bool ret = false;

		LockList(c->UnixVLanList);
		{
			for (i = 0;i < LIST_NUM(c->UnixVLanList);i++)
			{
				v = (UNIX_VLAN *)LIST_DATA(c->UnixVLanList, i);
				if (StrCmpi(v->Name, name) == 0)
				{
					ret = true;
				}
			}
		}
		UnlockList(c->UnixVLanList);

		return ret;
	}
#endif	// OS_WIN32
}