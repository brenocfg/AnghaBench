#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_17__ {int Enabled; int /*<<< orphan*/  Name; } ;
typedef  TYPE_2__ UNIX_VLAN ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ClientSession; TYPE_1__* ClientOption; } ;
struct TYPE_19__ {int /*<<< orphan*/  UnixVLanList; int /*<<< orphan*/  AccountList; } ;
struct TYPE_18__ {int /*<<< orphan*/  DeviceName; } ;
struct TYPE_16__ {int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_3__ RPC_CLIENT_CREATE_VLAN ;
typedef  TYPE_4__ CLIENT ;
typedef  TYPE_5__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  CiNotify (TYPE_4__*) ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_4__*) ; 
 int /*<<< orphan*/  CiSendGlobalPulse (TYPE_4__*) ; 
 int /*<<< orphan*/  CiSetError (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_OBJECT_NOT_FOUND ; 
 TYPE_5__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool CtDisableVLan(CLIENT *c, RPC_CLIENT_CREATE_VLAN *vlan)
{
	UINT i;
	bool used;
	// Validate arguments
	if (c == NULL || vlan == NULL)
	{
		return false;
	}

#ifndef	OS_WIN32

#ifdef	NO_VLAN
	if (GetOsInfo()->OsType == OSTYPE_MACOS_X)
	{
		// Can not be added or removed the virtual LAN card in MacOS X
		CiSetError(c, ERR_NOT_SUPPORTED);
		return false;
	}
#endif	// NO_VLAN

	// Check whether the virtual LAN card with the specified name is not
	// being used by one or more accounts
	used = false;
	LockList(c->AccountList);
	{
		for (i = 0;i < LIST_NUM(c->AccountList);i++)
		{
			ACCOUNT *a = LIST_DATA(c->AccountList, i);
			if (StrCmpi(a->ClientOption->DeviceName, vlan->DeviceName) == 0)
			{
				Lock(a->lock);
				{
					if (a->ClientSession != NULL)
					{
						used = true;
					}
				}
				Unlock(a->lock);
			}
		}
	}
	UnlockList(c->AccountList);

	// Search for the virtual LAN card
	LockList(c->UnixVLanList);
	{
		UNIX_VLAN *v, t;

		Zero(&t, sizeof(t));
		StrCpy(t.Name, sizeof(t.Name), vlan->DeviceName);

		v = Search(c->UnixVLanList, &t);
		if (v == NULL)
		{
			UnlockList(c->UnixVLanList);
			CiSetError(c, ERR_OBJECT_NOT_FOUND);
			return false;
		}

		// Stop
		v->Enabled = false;
	}
	UnlockList(c->UnixVLanList);

	CiSaveConfigurationFile(c);
	CiNotify(c);
	CiSendGlobalPulse(c);

	return true;

#else	// OS_WIN32

	// Check whether the virtual LAN card with the specified name is not
	// being used by one or more accounts
	used = false;
	LockList(c->AccountList);
	{
		for (i = 0;i < LIST_NUM(c->AccountList);i++)
		{
			ACCOUNT *a = LIST_DATA(c->AccountList, i);
			if (StrCmpi(a->ClientOption->DeviceName, vlan->DeviceName) == 0)
			{
				Lock(a->lock);
				{
					if (a->ClientSession != NULL)
					{
						used = true;
					}
				}
				Unlock(a->lock);
			}
		}
	}
	UnlockList(c->AccountList);

#if	0
	if (used)
	{
		// In using
		CiSetError(c, ERR_VLAN_IS_USED);
		return false;
	}
#endif


	// Check whether the virtual LAN card are present
	if (MsIsVLanExists(VLAN_ADAPTER_NAME_TAG, vlan->DeviceName) == false &&
		MsIsVLanExists(VLAN_ADAPTER_NAME_TAG_OLD, vlan->DeviceName) == false)
	{
		CiSetError(c, ERR_OBJECT_NOT_FOUND);
		CiNotify(c);
		CiSendGlobalPulse(c);
		return false;
	}


	if (MsIs64BitWindows() && Is32() && MsIsAdmin())
	{
		// Execute the driver_installer to process since this Windows is 64 bit
		// but this code is 32 bit
		char tmp[MAX_SIZE];

		Format(tmp, sizeof(tmp), "disablevlan %s", vlan->DeviceName);

		if (MsExecDriverInstaller(tmp) == false)
		{
			CiSetError(c, ERR_VLAN_INSTALL_ERROR);
			CiNotify(c);
			CiSendGlobalPulse(c);
			return false;
		}
	}
	else
	{
		// Stop the virtual LAN card
		if (MsDisableVLan(vlan->DeviceName) == false)
		{
			CiSetError(c, ERR_VLAN_INSTALL_ERROR);
			CiNotify(c);
			CiSendGlobalPulse(c);
			return false;
		}
	}

	CiNotify(c);
	CiSendGlobalPulse(c);

	return true;

#endif	// OS_WIN32

}