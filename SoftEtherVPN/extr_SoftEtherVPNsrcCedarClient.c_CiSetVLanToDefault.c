#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_name ;
struct TYPE_8__ {char* Name; } ;
typedef  TYPE_2__ UNIX_VLAN ;
typedef  int UINT ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_1__* ClientOption; } ;
struct TYPE_9__ {int /*<<< orphan*/  AccountList; int /*<<< orphan*/  UnixVLanList; } ;
struct TYPE_7__ {char* DeviceName; } ;
typedef  TYPE_3__ CLIENT ;
typedef  TYPE_4__ ACCOUNT ;

/* Variables and functions */
 int CiIsVLan (TYPE_3__*,char*) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiSetVLanToDefault(CLIENT *c)
{
	char device_name[MAX_SIZE];
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

#ifdef	OS_WIN32
	{
		TOKEN_LIST *t;

		t = MsEnumNetworkAdapters(VLAN_ADAPTER_NAME, VLAN_ADAPTER_NAME_OLD);
		if (t == NULL)
		{
			return;
		}
		if (t->NumTokens != 1)
		{
			FreeToken(t);
			return;
		}
		StrCpy(device_name, sizeof(device_name), t->Token[0]);
		FreeToken(t);
	}
#else	// OS_WIN32
	{
		UNIX_VLAN *v;

		LockList(c->UnixVLanList);

		if (LIST_NUM(c->UnixVLanList) != 1)
		{
			UnlockList(c->UnixVLanList);
			return;
		}
		v = LIST_DATA(c->UnixVLanList, 0);
		StrCpy(device_name, sizeof(device_name), v->Name);

		UnlockList(c->UnixVLanList);
	}
#endif	// OS_WIN32

	{
		UINT i;
		LockList(c->AccountList);
		{
			for (i = 0;i < LIST_NUM(c->AccountList);i++)
			{
				ACCOUNT *a = LIST_DATA(c->AccountList, i);

				Lock(a->lock);
				{
					if (CiIsVLan(c, a->ClientOption->DeviceName) == false)
					{
						StrCpy(a->ClientOption->DeviceName, sizeof(a->ClientOption->DeviceName),
							device_name);
					}
				}
				Unlock(a->lock);
			}
		}
		UnlockList(c->AccountList);
	}
}