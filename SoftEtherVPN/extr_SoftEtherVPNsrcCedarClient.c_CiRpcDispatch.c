#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_3__ ;
typedef  struct TYPE_45__   TYPE_2__ ;
typedef  struct TYPE_44__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  a ;
struct TYPE_46__ {int /*<<< orphan*/  Err; } ;
struct TYPE_45__ {TYPE_3__* Param; } ;
struct TYPE_44__ {int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  RPC_USE_SECURE ;
typedef  int /*<<< orphan*/  RPC_RENAME_ACCOUNT ;
typedef  int /*<<< orphan*/  RPC_GET_ISSUER ;
typedef  int /*<<< orphan*/  RPC_GET_CA ;
typedef  int /*<<< orphan*/  RPC_ENUM_OBJECT_IN_SECURE ;
typedef  int /*<<< orphan*/  RPC_CLIENT_VERSION ;
typedef  int /*<<< orphan*/  RPC_CLIENT_SET_VLAN ;
typedef  int /*<<< orphan*/  RPC_CLIENT_PASSWORD_SETTING ;
typedef  int /*<<< orphan*/  RPC_CLIENT_PASSWORD ;
typedef  int /*<<< orphan*/  RPC_CLIENT_GET_VLAN ;
typedef  int /*<<< orphan*/  RPC_CLIENT_GET_CONNECTION_STATUS ;
typedef  int /*<<< orphan*/  RPC_CLIENT_GET_ACCOUNT ;
typedef  int /*<<< orphan*/  RPC_CLIENT_ENUM_VLAN ;
typedef  int /*<<< orphan*/  RPC_CLIENT_ENUM_SECURE ;
typedef  int /*<<< orphan*/  RPC_CLIENT_ENUM_CA ;
typedef  int /*<<< orphan*/  RPC_CLIENT_ENUM_ACCOUNT ;
typedef  int /*<<< orphan*/  RPC_CLIENT_DELETE_CA ;
typedef  int /*<<< orphan*/  RPC_CLIENT_DELETE_ACCOUNT ;
typedef  int /*<<< orphan*/  RPC_CLIENT_CREATE_VLAN ;
typedef  int /*<<< orphan*/  RPC_CLIENT_CREATE_ACCOUNT ;
typedef  int /*<<< orphan*/  RPC_CLIENT_CONNECT ;
typedef  TYPE_1__ RPC_CERT ;
typedef  TYPE_2__ RPC ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  INTERNET_SETTING ;
typedef  int /*<<< orphan*/  CM_SETTING ;
typedef  int /*<<< orphan*/  CLIENT_CONFIG ;
typedef  TYPE_3__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeClientCreateAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeClientEnumAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeClientEnumCa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeClientEnumSecure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeClientEnumVLan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeClientGetAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeClientGetConnectionStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeEnumObjectInSecure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeGetCa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeGetIssuer (int /*<<< orphan*/ *) ; 
 int CtAddCa (TYPE_3__*,TYPE_1__*) ; 
 int CtConnect (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtCreateAccount (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int CtCreateVLan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtDeleteAccount (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int CtDeleteCa (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtDeleteVLan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtDisableVLan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtDisconnect (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int CtEnableVLan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtEnumAccount (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtEnumCa (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtEnumObjectInSecure (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtEnumSecure (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtEnumVLan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtGetAccount (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtGetAccountStatus (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtGetCa (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtGetClientConfig (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtGetClientVersion (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtGetCmSetting (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CtGetCommonProxySetting (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CtGetIssuer (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtGetPasswordSetting (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtGetUseSecure (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtGetVLan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtRemoveStartupAccount (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtRenameAccount (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int CtSetAccount (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int CtSetClientConfig (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtSetCmSetting (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CtSetCommonProxySetting (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtSetPassword (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtSetStartupAccount (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int CtSetVLan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtUpgradeVLan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int CtUseSecure (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InRpcCert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientCreateAccount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientDeleteAccount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientDeleteCa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientGetAccount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientGetConnectionStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientGetVLan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientPassword (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientSetVLan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcCmSetting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcCreateVLan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcGetCa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcGetIssuer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcInternetSetting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcRenameAccount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcUseSecure (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcClientConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcClientEnumAccount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcClientEnumCa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcClientEnumSecure (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcClientEnumVLan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcClientGetAccount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcClientGetConnectionStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcClientGetVLan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcClientPasswordSetting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcClientVersion (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcCmSetting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcEnumObjectInSecure (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcGetCa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcGetIssuer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcInternetSetting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcUseSecure (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

PACK *CiRpcDispatch(RPC *rpc, char *name, PACK *p)
{
	PACK *ret;
	CLIENT *c;
	// Validate arguments
	if (rpc == NULL || name == NULL || p == NULL)
	{
		return NULL;
	}
	c = rpc->Param;

	ret = NewPack();

	if (StrCmpi(name, "GetClientVersion") == 0)
	{
		RPC_CLIENT_VERSION a;
		if (CtGetClientVersion(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientVersion(ret, &a);
		}
	}
	else if (StrCmpi(name, "GetCmSetting") == 0)
	{
		CM_SETTING a;
		if (CtGetCmSetting(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcCmSetting(ret, &a);
		}
	}
	else if (StrCmpi(name, "SetCmSetting") == 0)
	{
		CM_SETTING a;
		Zero(&a, sizeof(a));
		InRpcCmSetting(&a, p);
		if (CtSetCmSetting(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "SetPassword") == 0)
	{
		RPC_CLIENT_PASSWORD a;
		InRpcClientPassword(&a, p);
		if (CtSetPassword(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "GetPasswordSetting") == 0)
	{
		RPC_CLIENT_PASSWORD_SETTING a;
		if (CtGetPasswordSetting(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientPasswordSetting(ret, &a);
		}
	}
	else if (StrCmpi(name, "EnumCa") == 0)
	{
		RPC_CLIENT_ENUM_CA a;
		if (CtEnumCa(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientEnumCa(ret, &a);
			CiFreeClientEnumCa(&a);
		}
	}
	else if (StrCmpi(name, "AddCa") == 0)
	{
		RPC_CERT a;
		InRpcCert(&a, p);
		if (CtAddCa(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		FreeX(a.x);
	}
	else if (StrCmpi(name, "DeleteCa") == 0)
	{
		RPC_CLIENT_DELETE_CA a;
		InRpcClientDeleteCa(&a, p);
		if (CtDeleteCa(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "GetCa") == 0)
	{
		RPC_GET_CA a;
		InRpcGetCa(&a, p);
		if (CtGetCa(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcGetCa(ret, &a);
		}
		CiFreeGetCa(&a);
	}
	else if (StrCmpi(name, "EnumSecure") == 0)
	{
		RPC_CLIENT_ENUM_SECURE a;
		if (CtEnumSecure(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientEnumSecure(ret, &a);
			CiFreeClientEnumSecure(&a);
		}
	}
	else if (StrCmpi(name, "UseSecure") == 0)
	{
		RPC_USE_SECURE a;
		InRpcUseSecure(&a, p);
		if (CtUseSecure(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "GetUseSecure") == 0)
	{
		RPC_USE_SECURE a;
		Zero(&a, sizeof(a));
		if (CtGetUseSecure(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcUseSecure(ret, &a);
		}
	}
	else if (StrCmpi(name, "EnumObjectInSecure") == 0)
	{
		RPC_ENUM_OBJECT_IN_SECURE a;
		if (CtEnumObjectInSecure(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcEnumObjectInSecure(ret, &a);
			CiFreeEnumObjectInSecure(&a);
		}
	}
	else if (StrCmpi(name, "CreateVLan") == 0)
	{
		RPC_CLIENT_CREATE_VLAN a;
		InRpcCreateVLan(&a, p);
		if (CtCreateVLan(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "UpgradeVLan") == 0)
	{
		RPC_CLIENT_CREATE_VLAN a;
		InRpcCreateVLan(&a, p);
		if (CtUpgradeVLan(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "GetVLan") == 0)
	{
		RPC_CLIENT_GET_VLAN a;
		InRpcClientGetVLan(&a, p);
		if (CtGetVLan(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientGetVLan(ret, &a);
		}
	}
	else if (StrCmpi(name, "SetVLan") == 0)
	{
		RPC_CLIENT_SET_VLAN a;
		InRpcClientSetVLan(&a, p);
		if (CtSetVLan(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "EnumVLan") == 0)
	{
		RPC_CLIENT_ENUM_VLAN a;
		if (CtEnumVLan(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientEnumVLan(ret, &a);
			CiFreeClientEnumVLan(&a);
		}
	}
	else if (StrCmpi(name, "DeleteVLan") == 0)
	{
		RPC_CLIENT_CREATE_VLAN a;
		InRpcCreateVLan(&a, p);
		if (CtDeleteVLan(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "EnableVLan") == 0)
	{
		RPC_CLIENT_CREATE_VLAN a;
		InRpcCreateVLan(&a, p);
		if (CtEnableVLan(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "DisableVLan") == 0)
	{
		RPC_CLIENT_CREATE_VLAN a;
		InRpcCreateVLan(&a, p);
		if (CtDisableVLan(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "CreateAccount") == 0)
	{
		RPC_CLIENT_CREATE_ACCOUNT a;
		InRpcClientCreateAccount(&a, p);
		if (CtCreateAccount(c, &a, false) == false)
		{
			RpcError(ret, c->Err);
		}
		CiFreeClientCreateAccount(&a);
	}
	else if (StrCmpi(name, "EnumAccount") == 0)
	{
		RPC_CLIENT_ENUM_ACCOUNT a;
		if (CtEnumAccount(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientEnumAccount(ret, &a);
			CiFreeClientEnumAccount(&a);
		}
	}
	else if (StrCmpi(name, "DeleteAccount") == 0)
	{
		RPC_CLIENT_DELETE_ACCOUNT a;
		InRpcClientDeleteAccount(&a, p);
		if (CtDeleteAccount(c, &a, false) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "SetStartupAccount") == 0)
	{
		RPC_CLIENT_DELETE_ACCOUNT a;
		InRpcClientDeleteAccount(&a, p);
		if (CtSetStartupAccount(c, &a, false) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "RemoveStartupAccount") == 0)
	{
		RPC_CLIENT_DELETE_ACCOUNT a;
		InRpcClientDeleteAccount(&a, p);
		if (CtRemoveStartupAccount(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "GetIssuer") == 0)
	{
		RPC_GET_ISSUER a;
		InRpcGetIssuer(&a, p);
		if (CtGetIssuer(c, &a))
		{
			OutRpcGetIssuer(ret, &a);
		}
		else
		{
			RpcError(ret, c->Err);
		}
		CiFreeGetIssuer(&a);
	}
	else if (StrCmpi(name, "GetCommonProxySetting") == 0)
	{
		INTERNET_SETTING t;
		InRpcInternetSetting(&t, p);
		if (CtGetCommonProxySetting(c, &t))
		{
			OutRpcInternetSetting(ret, &t);
		}
		else
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "SetCommonProxySetting") == 0)
	{
		INTERNET_SETTING t;
		InRpcInternetSetting(&t, p);
		if (CtSetCommonProxySetting(c, &t))
		{
			OutRpcInternetSetting(ret, &t);
		}
		else
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "SetAccount") == 0)
	{
		RPC_CLIENT_CREATE_ACCOUNT a;
		InRpcClientCreateAccount(&a, p);
		if (CtSetAccount(c, &a, false) == false)
		{
			RpcError(ret, c->Err);
		}
		CiFreeClientCreateAccount(&a);
	}
	else if (StrCmpi(name, "GetAccount") == 0)
	{
		RPC_CLIENT_GET_ACCOUNT a;
		InRpcClientGetAccount(&a, p);
		if (CtGetAccount(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientGetAccount(ret, &a);
		}
		CiFreeClientGetAccount(&a);
	}
	else if (StrCmpi(name, "RenameAccount") == 0)
	{
		RPC_RENAME_ACCOUNT a;
		InRpcRenameAccount(&a, p);
		if (CtRenameAccount(c, &a, false) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "SetClientConfig") == 0)
	{
		CLIENT_CONFIG a;
		InRpcClientConfig(&a, p);
		if (CtSetClientConfig(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "GetClientConfig") == 0)
	{
		CLIENT_CONFIG a;
		if (CtGetClientConfig(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientConfig(ret, &a);
		}
	}
	else if (StrCmpi(name, "Connect") == 0)
	{
		RPC_CLIENT_CONNECT a;
		InRpcClientConnect(&a, p);
		if (CtConnect(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "Disconnect") == 0)
	{
		RPC_CLIENT_CONNECT a;
		InRpcClientConnect(&a, p);
		if (CtDisconnect(c, &a, false) == false)
		{
			RpcError(ret, c->Err);
		}
	}
	else if (StrCmpi(name, "GetAccountStatus") == 0)
	{
		RPC_CLIENT_GET_CONNECTION_STATUS a;
		InRpcClientGetConnectionStatus(&a, p);
		if (CtGetAccountStatus(c, &a) == false)
		{
			RpcError(ret, c->Err);
		}
		else
		{
			OutRpcClientGetConnectionStatus(ret, &a);
		}
		CiFreeClientGetConnectionStatus(&a);
	}
	else
	{
		FreePack(ret);
		ret = NULL;
	}

	return ret;
}