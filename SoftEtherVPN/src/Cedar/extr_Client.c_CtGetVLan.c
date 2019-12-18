#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Guid; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  FileName; int /*<<< orphan*/  Version; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  Enabled; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_VLAN ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CiSetError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* MsGetDriverFileName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* MsGetDriverVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* MsGetMacAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* MsGetNetworkAdapterGuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsIsVLanEnabled (int /*<<< orphan*/ ) ; 
 int MsIsVLanExists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VLAN_ADAPTER_NAME_TAG ; 
 int /*<<< orphan*/  VLAN_ADAPTER_NAME_TAG_OLD ; 

bool CtGetVLan(CLIENT *c, RPC_CLIENT_GET_VLAN *get)
{
	char *tmp;
	// Validate arguments
	if (c == NULL || get == NULL)
	{
		return false;
	}

#ifndef	OS_WIN32

	// Unsupported
	CiSetError(c, ERR_NOT_SUPPORTED);
	return false;

#else	// OS_WIN32

	// Check whether the virtual LAN card with the specified name already exists
	if (MsIsVLanExists(VLAN_ADAPTER_NAME_TAG, get->DeviceName) == false &&
		MsIsVLanExists(VLAN_ADAPTER_NAME_TAG_OLD, get->DeviceName) == false)
	{
		// Not exist
		CiSetError(c, ERR_OBJECT_NOT_FOUND);
		return false;
	}

	// Activity
	get->Enabled = MsIsVLanEnabled(get->DeviceName);

	// MAC address
	tmp = MsGetMacAddress(VLAN_ADAPTER_NAME_TAG, get->DeviceName);
	if (tmp == NULL)
	{
		tmp = MsGetMacAddress(VLAN_ADAPTER_NAME_TAG_OLD, get->DeviceName);
	}
	StrCpy(get->MacAddress, sizeof(get->MacAddress), tmp);
	Free(tmp);

	// Version
	tmp = MsGetDriverVersion(VLAN_ADAPTER_NAME_TAG, get->DeviceName);
	if (tmp == NULL)
	{
		tmp = MsGetDriverVersion(VLAN_ADAPTER_NAME_TAG_OLD, get->DeviceName);
	}
	StrCpy(get->Version, sizeof(get->Version), tmp);
	Free(tmp);

	// File name
	tmp = MsGetDriverFileName(VLAN_ADAPTER_NAME_TAG, get->DeviceName);
	if (tmp == NULL)
	{
		tmp = MsGetDriverFileName(VLAN_ADAPTER_NAME_TAG_OLD, get->DeviceName);
	}
	StrCpy(get->FileName, sizeof(get->FileName), tmp);
	Free(tmp);

	// GUID
	tmp = MsGetNetworkAdapterGuid(VLAN_ADAPTER_NAME_TAG, get->DeviceName);
	if (tmp == NULL)
	{
		tmp = MsGetNetworkAdapterGuid(VLAN_ADAPTER_NAME_TAG_OLD, get->DeviceName);
	}
	StrCpy(get->Guid, sizeof(get->Guid), tmp);
	Free(tmp);

	return true;

#endif	// OS_WIN32
}