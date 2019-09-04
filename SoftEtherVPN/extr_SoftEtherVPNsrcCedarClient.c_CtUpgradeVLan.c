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
typedef  int /*<<< orphan*/  RPC_CLIENT_CREATE_VLAN ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */

bool CtUpgradeVLan(CLIENT *c, RPC_CLIENT_CREATE_VLAN *create)
{
	bool use_old_name = false;

#ifdef	OS_WIN32
	KAKUSHI *k = NULL;
	MS_DRIVER_VER ver;
#endif	// OS_WIN32

	// Validate arguments
	if (c == NULL || create == NULL)
	{
		return false;
	}


#ifndef	OS_WIN32

	// Always succeed
	return true;

#else	// OS_WIN32

	CiInitDriverVerStruct(&ver);

	if (MsIsNt() == false)
	{
		// Not available in Win9x
		CiSetError(c, ERR_NOT_SUPPORTED);
		return false;
	}

	// Check whether the LAN card with the specified name already exists
	if (MsIsVLanExists(VLAN_ADAPTER_NAME_TAG, create->DeviceName) == false &&
		MsIsVLanExists(VLAN_ADAPTER_NAME_TAG_OLD, create->DeviceName) == false)
	{
		// Not exist
		CiSetError(c, ERR_OBJECT_NOT_FOUND);
		CiNotify(c);
		CiSendGlobalPulse(c);
		return false;
	}

	if (MsIsVLanExists(VLAN_ADAPTER_NAME_TAG_OLD, create->DeviceName))
	{
		use_old_name = true;
	}

	if (MsIsVista() == false)
	{
		k = InitKakushi();	
	}


	if (MsIsVista() == false)
	{
		// Perform the installation (other than Windows Vista)
		if (MsUpgradeVLan(use_old_name ? VLAN_ADAPTER_NAME_TAG_OLD : VLAN_ADAPTER_NAME_TAG,
			use_old_name ? VLAN_CONNECTION_NAME_OLD : VLAN_CONNECTION_NAME,
			create->DeviceName, &ver) == false)
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

		Format(tmp, sizeof(tmp), "upgradevlan %s", create->DeviceName);

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

	CLog(c, "LC_UPDATE_VLAN", create->DeviceName);

	CiNotify(c);
	CiSendGlobalPulse(c);

	return true;

#endif	// OS_WIN32
}