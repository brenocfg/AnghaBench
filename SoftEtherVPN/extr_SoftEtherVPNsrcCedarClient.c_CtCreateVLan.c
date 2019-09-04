#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_20__ {int Enabled; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  Name; } ;
typedef  TYPE_2__ UNIX_VLAN ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_19__ {int /*<<< orphan*/  NicDownOnDisconnect; } ;
struct TYPE_22__ {int /*<<< orphan*/  UnixVLanList; TYPE_1__ Config; } ;
struct TYPE_21__ {int /*<<< orphan*/  DeviceName; } ;
typedef  int /*<<< orphan*/  TOKEN_LIST ;
typedef  TYPE_3__ RPC_CLIENT_CREATE_VLAN ;
typedef  TYPE_4__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CLog (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiNormalizeAccountVLan (TYPE_4__*) ; 
 int /*<<< orphan*/  CiNotify (TYPE_4__*) ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_4__*) ; 
 int /*<<< orphan*/  CiSendGlobalPulse (TYPE_4__*) ; 
 int /*<<< orphan*/  CiSetError (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_VLAN_ALREADY_EXISTS ; 
 int /*<<< orphan*/  ERR_VLAN_INSTALL_ERROR ; 
 int /*<<< orphan*/  ERR_VLAN_INVALID_NAME ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  GenMacAddress (int /*<<< orphan*/ ) ; 
 scalar_t__ INFINITE ; 
 int IsSafeStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ SearchStrEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int UnixVLanCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

bool CtCreateVLan(CLIENT *c, RPC_CLIENT_CREATE_VLAN *create)
{
	TOKEN_LIST *t;
	UINT max_len;

#ifdef	OS_WIN32
	KAKUSHI *k = NULL;
#endif	// OS_WIN32

	// Validate arguments
	if (c == NULL || create == NULL)
	{
		return false;
	}

	if (SearchStrEx(create->DeviceName, " ", 0, false) != INFINITE)
	{
		// Spaces in the name is not allowed
		CiSetError(c, ERR_INVALID_PARAMETER);
		return false;
	}

#ifndef	OS_WIN32

	// Non-Win32
#ifdef	NO_VLAN
	if (GetOsInfo()->OsType == OSTYPE_MACOS_X)
	{
		// A virtual LAN card can not be added or removed in MacOS X
		CiSetError(c, ERR_NOT_SUPPORTED);
		return false;
	}
#endif	// NO_VLAN

	// Check whether the specified name is valid or not
	if (IsSafeStr(create->DeviceName) == false)
	{
		// Name is invalid
		CiSetError(c, ERR_VLAN_INVALID_NAME);
		return false;
	}

	// Check whether the LAN card of the specified name already exists
	LockList(c->UnixVLanList);
	{
		UNIX_VLAN t, *r;
		Zero(&t, sizeof(t));
		StrCpy(t.Name, sizeof(t.Name), create->DeviceName);

		r = Search(c->UnixVLanList, &t);
		if (r != NULL)
		{
			// Already exist
			CiSetError(c, ERR_VLAN_ALREADY_EXISTS);
			UnlockList(c->UnixVLanList);
			return false;
		}

		// Register
		r = ZeroMalloc(sizeof(UNIX_VLAN));
		r->Enabled = true;
		GenMacAddress(r->MacAddress);
		StrCpy(r->Name, sizeof(r->Name), create->DeviceName);

		// Create a TUN
		if (UnixVLanCreate(r->Name, r->MacAddress, !c->Config.NicDownOnDisconnect) == false)
		{
			// Failure
			Free(r);
			CiSetError(c, ERR_VLAN_INSTALL_ERROR);
			UnlockList(c->UnixVLanList);
			return false;
		}

		CLog(c, "LC_CREATE_VLAN", create->DeviceName);

		Add(c->UnixVLanList, r);
	}
	UnlockList(c->UnixVLanList);

	CiNormalizeAccountVLan(c);

	CiNotify(c);
	CiSendGlobalPulse(c);
	CiSaveConfigurationFile(c);

	return true;

#else	// OS_WIN32

	if (OS_IS_WINDOWS_9X(GetOsInfo()->OsType))
	{
		// Only one LAN card is available in the Win9x
		TOKEN_LIST *t;

		t = MsEnumNetworkAdapters(VLAN_ADAPTER_NAME, VLAN_ADAPTER_NAME_OLD);
		if (t != NULL)
		{
			if (t->NumTokens >= 1)
			{
				FreeToken(t);
				CiSetError(c, ERR_NOT_SUPPORTED);
				return false;
			}
			FreeToken(t);
		}
	}

	// Check whether the specified name is valid or not
	if (IsSafeStr(create->DeviceName) == false)
	{
		// Name is invalid
		CiSetError(c, ERR_VLAN_INVALID_NAME);
		return false;
	}

	max_len = MsIsNt() ? MAX_DEVICE_NAME_LEN : MAX_DEVICE_NAME_LEN_9X;
	if (StrLen(create->DeviceName) > max_len)
	{
		// Name is too long
		CiSetError(c, ERR_VLAN_INVALID_NAME);
		return false;
	}

	// Regulation in Windows 8 / 10
	if (MsIsInfCatalogRequired())
	{
		if (CiIsValidVLanRegulatedName(create->DeviceName) == false)
		{
			// Name is invalid
			CiSetError(c, ERR_VLAN_INVALID_NAME);
			return false;
		}
	}

	// Check whether the LAN card with the specified name already exists
	if (MsIsVLanExists(VLAN_ADAPTER_NAME_TAG, create->DeviceName) ||
		MsIsVLanExists(VLAN_ADAPTER_NAME_TAG_OLD, create->DeviceName))
	{
		// Already exist
		CiSetError(c, ERR_VLAN_ALREADY_EXISTS);
		return false;
	}

	if (MsIsNt())
	{
		if (MsIsVista() == false)
		{
			k = InitKakushi();
		}
	}

	if (MsIsVista() == false)
	{
		MS_DRIVER_VER ver;

		CiInitDriverVerStruct(&ver);

		// Perform the installation (other than Windows Vista)
		if (MsInstallVLan(VLAN_ADAPTER_NAME_TAG, VLAN_CONNECTION_NAME, create->DeviceName, &ver) == false)
		{
			// Installation Failed
			FreeKakushi(k);
			CiSetError(c, ERR_VLAN_INSTALL_ERROR);
			CiNotify(c);
			CiSendGlobalPulse(c);
			return false;
		}
	}
	else
	{
		// Perform the installation (Windows Vista)
		char tmp[MAX_SIZE];

		Format(tmp, sizeof(tmp), "instvlan %s", create->DeviceName);

		if (CncExecDriverInstaller(tmp) == false)
		{
			// Installation Failed
			FreeKakushi(k);
			CiSetError(c, ERR_VLAN_INSTALL_ERROR);
			CiNotify(c);
			CiSendGlobalPulse(c);
			return false;
		}
	}

	FreeKakushi(k);

	t = MsEnumNetworkAdapters(VLAN_ADAPTER_NAME, VLAN_ADAPTER_NAME_OLD);
	if (t->NumTokens == 1)
	{
		UINT i;
		// If the result of the installation, virtual LAN card is only one,
		// set virtual LAN card setting of all existing accounts to this virtual LAN card
		LockList(c->AccountList);
		{
			for (i = 0;i < LIST_NUM(c->AccountList);i++)
			{
				ACCOUNT *a = LIST_DATA(c->AccountList, i);
				Lock(a->lock);
				{
					if (a->ClientOption != NULL)
					{
						StrCpy(a->ClientOption->DeviceName, sizeof(a->ClientOption->DeviceName), create->DeviceName);
					}
				}
				Unlock(a->lock);
			}
		}
		UnlockList(c->AccountList);
	}
	FreeToken(t);

	CLog(c, "LC_CREATE_VLAN", create->DeviceName);

	CiNormalizeAccountVLan(c);

	CiNotify(c);
	CiSendGlobalPulse(c);

	CiSaveConfigurationFile(c);

	if (MsIsNt() == false)
	{
		if (GetOsInfo()->OsType == OSTYPE_WINDOWS_ME)
		{
			// Show the warning in the case of Windows Me
			MsgBox(NULL, 0x00000040L, _UU("CM_9X_VLAN_ME_MESSAGE"));
		}

		ReleaseThread(NewThread(Win9xRebootThread, NULL));
	}

	return true;

#endif	// OS_WIN32
}