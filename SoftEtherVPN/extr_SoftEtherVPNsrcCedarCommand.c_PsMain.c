#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  prompt ;
typedef  int /*<<< orphan*/  cmd ;
typedef  scalar_t__ UINT ;
struct TYPE_31__ {scalar_t__ ConsoleType; scalar_t__ RetCode; int /*<<< orphan*/  (* Write ) (TYPE_6__*,char*) ;} ;
struct TYPE_30__ {char* member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_29__ {scalar_t__ LastError; int /*<<< orphan*/ * CapsList; int /*<<< orphan*/ * CmdLine; TYPE_6__* Console; int /*<<< orphan*/ * HubName; int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * AdminHub; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerName; } ;
struct TYPE_28__ {TYPE_1__* Cert; int /*<<< orphan*/ * HubName; } ;
struct TYPE_27__ {int has_basic_constraints; scalar_t__ root_cert; } ;
typedef  TYPE_2__ RPC_KEY_PAIR ;
typedef  TYPE_2__ RPC_HUB_STATUS ;
typedef  TYPE_4__ PS ;
typedef  TYPE_5__ CMD ;

/* Variables and functions */
 scalar_t__ CONSOLE_CSV ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/ * CopyStr (int /*<<< orphan*/ *) ; 
 int DispatchNextCmdEx (TYPE_6__*,int /*<<< orphan*/ *,char*,TYPE_5__*,int,TYPE_4__*) ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Format (char*,int,char*,...) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeCapsList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcKeyPair (TYPE_2__*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  PsAbout ; 
 int /*<<< orphan*/  PsAcAdd ; 
 int /*<<< orphan*/  PsAcAdd6 ; 
 int /*<<< orphan*/  PsAcDel ; 
 int /*<<< orphan*/  PsAcList ; 
 int /*<<< orphan*/  PsAccessAdd ; 
 int /*<<< orphan*/  PsAccessAdd6 ; 
 int /*<<< orphan*/  PsAccessAddEx ; 
 int /*<<< orphan*/  PsAccessAddEx6 ; 
 int /*<<< orphan*/  PsAccessDelete ; 
 int /*<<< orphan*/  PsAccessDisable ; 
 int /*<<< orphan*/  PsAccessEnable ; 
 int /*<<< orphan*/  PsAccessList ; 
 int /*<<< orphan*/  PsAdminOptionList ; 
 int /*<<< orphan*/  PsAdminOptionSet ; 
 int /*<<< orphan*/  PsBridgeCreate ; 
 int /*<<< orphan*/  PsBridgeDelete ; 
 int /*<<< orphan*/  PsBridgeDeviceList ; 
 int /*<<< orphan*/  PsBridgeList ; 
 int /*<<< orphan*/  PsCAAdd ; 
 int /*<<< orphan*/  PsCADelete ; 
 int /*<<< orphan*/  PsCAGet ; 
 int /*<<< orphan*/  PsCAList ; 
 int /*<<< orphan*/  PsCaps ; 
 int /*<<< orphan*/  PsCascadeAnonymousSet ; 
 int /*<<< orphan*/  PsCascadeCertGet ; 
 int /*<<< orphan*/  PsCascadeCertSet ; 
 int /*<<< orphan*/  PsCascadeCompressDisable ; 
 int /*<<< orphan*/  PsCascadeCompressEnable ; 
 int /*<<< orphan*/  PsCascadeCreate ; 
 int /*<<< orphan*/  PsCascadeDelete ; 
 int /*<<< orphan*/  PsCascadeDetailSet ; 
 int /*<<< orphan*/  PsCascadeEncryptDisable ; 
 int /*<<< orphan*/  PsCascadeEncryptEnable ; 
 int /*<<< orphan*/  PsCascadeGet ; 
 int /*<<< orphan*/  PsCascadeHttpHeaderAdd ; 
 int /*<<< orphan*/  PsCascadeHttpHeaderDelete ; 
 int /*<<< orphan*/  PsCascadeHttpHeaderGet ; 
 int /*<<< orphan*/  PsCascadeList ; 
 int /*<<< orphan*/  PsCascadeOffline ; 
 int /*<<< orphan*/  PsCascadeOnline ; 
 int /*<<< orphan*/  PsCascadePasswordSet ; 
 int /*<<< orphan*/  PsCascadePolicySet ; 
 int /*<<< orphan*/  PsCascadeProxyHttp ; 
 int /*<<< orphan*/  PsCascadeProxyNone ; 
 int /*<<< orphan*/  PsCascadeProxySocks ; 
 int /*<<< orphan*/  PsCascadeProxySocks5 ; 
 int /*<<< orphan*/  PsCascadeRename ; 
 int /*<<< orphan*/  PsCascadeServerCertDelete ; 
 int /*<<< orphan*/  PsCascadeServerCertDisable ; 
 int /*<<< orphan*/  PsCascadeServerCertEnable ; 
 int /*<<< orphan*/  PsCascadeServerCertGet ; 
 int /*<<< orphan*/  PsCascadeServerCertSet ; 
 int /*<<< orphan*/  PsCascadeSet ; 
 int /*<<< orphan*/  PsCascadeStatusGet ; 
 int /*<<< orphan*/  PsCascadeUsernameSet ; 
 int /*<<< orphan*/  PsClusterConnectionStatusGet ; 
 int /*<<< orphan*/  PsClusterMemberCertGet ; 
 int /*<<< orphan*/  PsClusterMemberInfoGet ; 
 int /*<<< orphan*/  PsClusterMemberList ; 
 int /*<<< orphan*/  PsClusterSettingController ; 
 int /*<<< orphan*/  PsClusterSettingGet ; 
 int /*<<< orphan*/  PsClusterSettingMember ; 
 int /*<<< orphan*/  PsClusterSettingStandalone ; 
 int /*<<< orphan*/  PsConfigGet ; 
 int /*<<< orphan*/  PsConfigSet ; 
 int /*<<< orphan*/  PsConnectionDisconnect ; 
 int /*<<< orphan*/  PsConnectionGet ; 
 int /*<<< orphan*/  PsConnectionList ; 
 int /*<<< orphan*/  PsCrash ; 
 int /*<<< orphan*/  PsCrlAdd ; 
 int /*<<< orphan*/  PsCrlDel ; 
 int /*<<< orphan*/  PsCrlGet ; 
 int /*<<< orphan*/  PsCrlList ; 
 int /*<<< orphan*/  PsDebug ; 
 int /*<<< orphan*/  PsDhcpDisable ; 
 int /*<<< orphan*/  PsDhcpEnable ; 
 int /*<<< orphan*/  PsDhcpGet ; 
 int /*<<< orphan*/  PsDhcpSet ; 
 int /*<<< orphan*/  PsDhcpTable ; 
 int /*<<< orphan*/  PsDynamicDnsGetStatus ; 
 int /*<<< orphan*/  PsDynamicDnsSetHostname ; 
 int /*<<< orphan*/  PsEtherIpClientAdd ; 
 int /*<<< orphan*/  PsEtherIpClientDelete ; 
 int /*<<< orphan*/  PsEtherIpClientList ; 
 int /*<<< orphan*/  PsExtOptionList ; 
 int /*<<< orphan*/  PsExtOptionSet ; 
 int /*<<< orphan*/  PsFlush ; 
 int /*<<< orphan*/  PsGroupCreate ; 
 int /*<<< orphan*/  PsGroupDelete ; 
 int /*<<< orphan*/  PsGroupGet ; 
 int /*<<< orphan*/  PsGroupJoin ; 
 int /*<<< orphan*/  PsGroupList ; 
 int /*<<< orphan*/  PsGroupPolicyRemove ; 
 int /*<<< orphan*/  PsGroupPolicySet ; 
 int /*<<< orphan*/  PsGroupSet ; 
 int /*<<< orphan*/  PsGroupUnjoin ; 
 int /*<<< orphan*/  PsHub ; 
 int /*<<< orphan*/  PsHubCreate ; 
 int /*<<< orphan*/  PsHubCreateDynamic ; 
 int /*<<< orphan*/  PsHubCreateStatic ; 
 int /*<<< orphan*/  PsHubDelete ; 
 int /*<<< orphan*/  PsHubList ; 
 int /*<<< orphan*/  PsHubSetDynamic ; 
 int /*<<< orphan*/  PsHubSetStatic ; 
 int /*<<< orphan*/  PsIPsecEnable ; 
 int /*<<< orphan*/  PsIPsecGet ; 
 int /*<<< orphan*/  PsIpDelete ; 
 int /*<<< orphan*/  PsIpTable ; 
 int /*<<< orphan*/  PsKeepDisable ; 
 int /*<<< orphan*/  PsKeepEnable ; 
 int /*<<< orphan*/  PsKeepGet ; 
 int /*<<< orphan*/  PsKeepSet ; 
 int /*<<< orphan*/  PsLicenseAdd ; 
 int /*<<< orphan*/  PsLicenseDel ; 
 int /*<<< orphan*/  PsLicenseList ; 
 int /*<<< orphan*/  PsLicenseStatus ; 
 int /*<<< orphan*/  PsListenerCreate ; 
 int /*<<< orphan*/  PsListenerDelete ; 
 int /*<<< orphan*/  PsListenerDisable ; 
 int /*<<< orphan*/  PsListenerEnable ; 
 int /*<<< orphan*/  PsListenerList ; 
 int /*<<< orphan*/  PsLogDisable ; 
 int /*<<< orphan*/  PsLogEnable ; 
 int /*<<< orphan*/  PsLogFileGet ; 
 int /*<<< orphan*/  PsLogFileList ; 
 int /*<<< orphan*/  PsLogGet ; 
 int /*<<< orphan*/  PsLogPacketSaveType ; 
 int /*<<< orphan*/  PsLogSwitchSet ; 
 int /*<<< orphan*/  PsMacDelete ; 
 int /*<<< orphan*/  PsMacTable ; 
 int /*<<< orphan*/  PsNatDisable ; 
 int /*<<< orphan*/  PsNatEnable ; 
 int /*<<< orphan*/  PsNatGet ; 
 int /*<<< orphan*/  PsNatSet ; 
 int /*<<< orphan*/  PsNatTable ; 
 int /*<<< orphan*/  PsOffline ; 
 int /*<<< orphan*/  PsOnline ; 
 int /*<<< orphan*/  PsOpenVpnEnable ; 
 int /*<<< orphan*/  PsOpenVpnGet ; 
 int /*<<< orphan*/  PsOpenVpnMakeConfig ; 
 int /*<<< orphan*/  PsOpenVpnObfuscationEnable ; 
 int /*<<< orphan*/  PsOpenVpnObfuscationGet ; 
 int /*<<< orphan*/  PsOptionsGet ; 
 int /*<<< orphan*/  PsPolicyList ; 
 int /*<<< orphan*/  PsRadiusServerDelete ; 
 int /*<<< orphan*/  PsRadiusServerGet ; 
 int /*<<< orphan*/  PsRadiusServerSet ; 
 int /*<<< orphan*/  PsReboot ; 
 int /*<<< orphan*/  PsRouterAdd ; 
 int /*<<< orphan*/  PsRouterDelete ; 
 int /*<<< orphan*/  PsRouterIfAdd ; 
 int /*<<< orphan*/  PsRouterIfDel ; 
 int /*<<< orphan*/  PsRouterIfList ; 
 int /*<<< orphan*/  PsRouterList ; 
 int /*<<< orphan*/  PsRouterStart ; 
 int /*<<< orphan*/  PsRouterStop ; 
 int /*<<< orphan*/  PsRouterTableAdd ; 
 int /*<<< orphan*/  PsRouterTableDel ; 
 int /*<<< orphan*/  PsRouterTableList ; 
 int /*<<< orphan*/  PsSecureNatDisable ; 
 int /*<<< orphan*/  PsSecureNatEnable ; 
 int /*<<< orphan*/  PsSecureNatHostGet ; 
 int /*<<< orphan*/  PsSecureNatHostSet ; 
 int /*<<< orphan*/  PsSecureNatStatusGet ; 
 int /*<<< orphan*/  PsServerCertGet ; 
 int /*<<< orphan*/  PsServerCertRegenerate ; 
 int /*<<< orphan*/  PsServerCertSet ; 
 int /*<<< orphan*/  PsServerCipherGet ; 
 int /*<<< orphan*/  PsServerCipherSet ; 
 int /*<<< orphan*/  PsServerInfoGet ; 
 int /*<<< orphan*/  PsServerKeyGet ; 
 int /*<<< orphan*/  PsServerPasswordSet ; 
 int /*<<< orphan*/  PsServerStatusGet ; 
 int /*<<< orphan*/  PsSessionDisconnect ; 
 int /*<<< orphan*/  PsSessionGet ; 
 int /*<<< orphan*/  PsSessionList ; 
 int /*<<< orphan*/  PsSetEnumAllow ; 
 int /*<<< orphan*/  PsSetEnumDeny ; 
 int /*<<< orphan*/  PsSetHubPassword ; 
 int /*<<< orphan*/  PsSetMaxSession ; 
 int /*<<< orphan*/  PsSstpEnable ; 
 int /*<<< orphan*/  PsSstpGet ; 
 int /*<<< orphan*/  PsStatusGet ; 
 int /*<<< orphan*/  PsSyslogDisable ; 
 int /*<<< orphan*/  PsSyslogEnable ; 
 int /*<<< orphan*/  PsSyslogGet ; 
 int /*<<< orphan*/  PsUserAnonymousSet ; 
 int /*<<< orphan*/  PsUserCertGet ; 
 int /*<<< orphan*/  PsUserCertSet ; 
 int /*<<< orphan*/  PsUserCreate ; 
 int /*<<< orphan*/  PsUserDelete ; 
 int /*<<< orphan*/  PsUserExpiresSet ; 
 int /*<<< orphan*/  PsUserGet ; 
 int /*<<< orphan*/  PsUserList ; 
 int /*<<< orphan*/  PsUserNTLMSet ; 
 int /*<<< orphan*/  PsUserPasswordSet ; 
 int /*<<< orphan*/  PsUserPolicyRemove ; 
 int /*<<< orphan*/  PsUserPolicySet ; 
 int /*<<< orphan*/  PsUserRadiusSet ; 
 int /*<<< orphan*/  PsUserSet ; 
 int /*<<< orphan*/  PsUserSignedSet ; 
 int /*<<< orphan*/  PsVpnAzureGetStatus ; 
 int /*<<< orphan*/  PsVpnAzureSetEnable ; 
 int /*<<< orphan*/  PsVpnOverIcmpDnsEnable ; 
 int /*<<< orphan*/  PsVpnOverIcmpDnsGet ; 
 int /*<<< orphan*/  PtCheck ; 
 int /*<<< orphan*/  PtMakeCert ; 
 int /*<<< orphan*/  PtMakeCert2048 ; 
 int /*<<< orphan*/  PtTrafficClient ; 
 int /*<<< orphan*/  PtTrafficServer ; 
 int /*<<< orphan*/ * ScGetCapsEx (int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetHubStatus (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ScGetServerCert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub10 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub11 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub12 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub6 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub7 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub8 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub9 (TYPE_6__*,char*) ; 

void PsMain(PS *ps)
{
	char prompt[MAX_SIZE];
	wchar_t tmp[MAX_SIZE];
	// Validate arguments
	if (ps == NULL)
	{
		return;
	}

	// If it's not in CSV mode, to display a message that the connection has been made
	if(ps->Console->ConsoleType != CONSOLE_CSV)
	{
		UniFormat(tmp, sizeof(tmp), _UU("CMD_VPNCMD_SERVER_CONNECTED"),
			ps->ServerName, ps->ServerPort);
		ps->Console->Write(ps->Console, tmp);
		ps->Console->Write(ps->Console, L"");

		if (ps->HubName == NULL)
		{
			// Server management mode
			ps->Console->Write(ps->Console, _UU("CMD_VPNCMD_SERVER_CONNECTED_1"));
		}
		else
		{
			// Virtual HUB management mode
			UniFormat(tmp, sizeof(tmp), _UU("CMD_VPNCMD_SERVER_CONNECTED_2"),
				ps->HubName);
			ps->Console->Write(ps->Console, tmp);
		}
		ps->Console->Write(ps->Console, L"");
	}

	// Get the Caps
	ps->CapsList = ScGetCapsEx(ps->Rpc);

	if (ps->AdminHub != NULL)
	{
		RPC_HUB_STATUS t;
		UINT ret;
		wchar_t tmp[MAX_SIZE];

		// Choose the Virtual HUB that is specified in the ADMINHUB
		Zero(&t, sizeof(t));

		StrCpy(t.HubName, sizeof(t.HubName), ps->AdminHub);

		ret = ScGetHubStatus(ps->Rpc, &t);
		if (ret == ERR_NO_ERROR)
		{
			// Success
			UniFormat(tmp, sizeof(tmp), _UU("CMD_Hub_Selected"), t.HubName);

			if (ps->HubName != NULL)
			{
				Free(ps->HubName);
			}
			ps->HubName = CopyStr(t.HubName);

			if( ps->Console->ConsoleType != CONSOLE_CSV)
			{
				ps->Console->Write(ps->Console, tmp);
			}
		}
		else
		{
			// Failure
			UniFormat(tmp, sizeof(tmp), _UU("CMD_Hub_Select_Failed"), ps->AdminHub);

			ps->Console->Write(ps->Console, tmp);
			CmdPrintError(ps->Console, ret);
		}
	}

	if (ps->HubName == NULL)
	{
		RPC_KEY_PAIR t;

		Zero(&t, sizeof(t));

		if (ScGetServerCert(ps->Rpc, &t) == ERR_NO_ERROR)
		{
			if (t.Cert != NULL && t.Cert->has_basic_constraints == false)
			{
				if (t.Cert->root_cert)
				{
					ps->Console->Write(ps->Console, L"");
					ps->Console->Write(ps->Console, _UU("SM_CERT_MESSAGE_CLI"));
					ps->Console->Write(ps->Console, L"");
				}
			}

			FreeRpcKeyPair(&t);
		}
	}

	while (true)
	{
		// Definition of command
		CMD cmd[] =
		{
			{"About", PsAbout},
			{"Check", PtCheck},
			{"Crash", PsCrash},
			{"Flush", PsFlush},
			{"Debug", PsDebug},
			{"ServerInfoGet", PsServerInfoGet},
			{"ServerStatusGet", PsServerStatusGet},
			{"ListenerCreate", PsListenerCreate},
			{"ListenerDelete", PsListenerDelete},
			{"ListenerList", PsListenerList},
			{"ListenerEnable", PsListenerEnable},
			{"ListenerDisable", PsListenerDisable},
			{"ServerPasswordSet", PsServerPasswordSet},
			{"ClusterSettingGet", PsClusterSettingGet},
			{"ClusterSettingStandalone", PsClusterSettingStandalone},
			{"ClusterSettingController", PsClusterSettingController},
			{"ClusterSettingMember", PsClusterSettingMember},
			{"ClusterMemberList", PsClusterMemberList},
			{"ClusterMemberInfoGet", PsClusterMemberInfoGet},
			{"ClusterMemberCertGet", PsClusterMemberCertGet},
			{"ClusterConnectionStatusGet", PsClusterConnectionStatusGet},
			{"ServerCertGet", PsServerCertGet},
			{"ServerKeyGet", PsServerKeyGet},
			{"ServerCertSet", PsServerCertSet},
			{"ServerCipherGet", PsServerCipherGet},
			{"ServerCipherSet", PsServerCipherSet},
			{"KeepEnable", PsKeepEnable},
			{"KeepDisable", PsKeepDisable},
			{"KeepSet", PsKeepSet},
			{"KeepGet", PsKeepGet},
			{"SyslogGet", PsSyslogGet},
			{"SyslogDisable", PsSyslogDisable},
			{"SyslogEnable", PsSyslogEnable},
			{"ConnectionList", PsConnectionList},
			{"ConnectionGet", PsConnectionGet},
			{"ConnectionDisconnect", PsConnectionDisconnect},
			{"BridgeDeviceList", PsBridgeDeviceList},
			{"BridgeList", PsBridgeList},
			{"BridgeCreate", PsBridgeCreate},
			{"BridgeDelete", PsBridgeDelete},
			{"Caps", PsCaps},
			{"Reboot", PsReboot},
			{"ConfigGet", PsConfigGet},
			{"ConfigSet", PsConfigSet},
			{"RouterList", PsRouterList},
			{"RouterAdd", PsRouterAdd},
			{"RouterDelete", PsRouterDelete},
			{"RouterStart", PsRouterStart},
			{"RouterStop", PsRouterStop},
			{"RouterIfList", PsRouterIfList},
			{"RouterIfAdd", PsRouterIfAdd},
			{"RouterIfDel", PsRouterIfDel},
			{"RouterTableList", PsRouterTableList},
			{"RouterTableAdd", PsRouterTableAdd},
			{"RouterTableDel", PsRouterTableDel},
			{"LogFileList", PsLogFileList},
			{"LogFileGet", PsLogFileGet},
			{"HubCreate", PsHubCreate},
			{"HubCreateDynamic", PsHubCreateDynamic},
			{"HubCreateStatic", PsHubCreateStatic},
			{"HubDelete", PsHubDelete},
			{"HubSetStatic", PsHubSetStatic},
			{"HubSetDynamic", PsHubSetDynamic},
			{"HubList", PsHubList},
			{"Hub", PsHub},
			{"Online", PsOnline},
			{"Offline", PsOffline},
			{"SetMaxSession", PsSetMaxSession},
			{"SetHubPassword", PsSetHubPassword},
			{"SetEnumAllow", PsSetEnumAllow},
			{"SetEnumDeny", PsSetEnumDeny},
			{"OptionsGet", PsOptionsGet},
			{"RadiusServerSet", PsRadiusServerSet},
			{"RadiusServerDelete", PsRadiusServerDelete},
			{"RadiusServerGet", PsRadiusServerGet},
			{"StatusGet", PsStatusGet},
			{"LogGet", PsLogGet},
			{"LogEnable", PsLogEnable},
			{"LogDisable", PsLogDisable},
			{"LogSwitchSet", PsLogSwitchSet},
			{"LogPacketSaveType", PsLogPacketSaveType},
			{"CAList", PsCAList},
			{"CAAdd", PsCAAdd},
			{"CADelete", PsCADelete},
			{"CAGet", PsCAGet},
			{"CascadeList", PsCascadeList},
			{"CascadeCreate", PsCascadeCreate},
			{"CascadeSet", PsCascadeSet},
			{"CascadeGet", PsCascadeGet},
			{"CascadeDelete", PsCascadeDelete},
			{"CascadeUsernameSet", PsCascadeUsernameSet},
			{"CascadeAnonymousSet", PsCascadeAnonymousSet},
			{"CascadePasswordSet", PsCascadePasswordSet},
			{"CascadeCertSet", PsCascadeCertSet},
			{"CascadeCertGet", PsCascadeCertGet},
			{"CascadeEncryptEnable", PsCascadeEncryptEnable},
			{"CascadeEncryptDisable", PsCascadeEncryptDisable},
			{"CascadeCompressEnable", PsCascadeCompressEnable},
			{"CascadeCompressDisable", PsCascadeCompressDisable},
			{"CascadeProxyNone", PsCascadeProxyNone},
			{"CascadeHttpHeaderAdd", PsCascadeHttpHeaderAdd},
			{"CascadeHttpHeaderDelete", PsCascadeHttpHeaderDelete},
			{"CascadeHttpHeaderGet", PsCascadeHttpHeaderGet},
			{"CascadeProxyHttp", PsCascadeProxyHttp},
			{"CascadeProxySocks", PsCascadeProxySocks},
			{"CascadeProxySocks5", PsCascadeProxySocks5},
			{"CascadeServerCertEnable", PsCascadeServerCertEnable},
			{"CascadeServerCertDisable", PsCascadeServerCertDisable},
			{"CascadeServerCertSet", PsCascadeServerCertSet},
			{"CascadeServerCertDelete", PsCascadeServerCertDelete},
			{"CascadeServerCertGet", PsCascadeServerCertGet},
			{"CascadeDetailSet", PsCascadeDetailSet},
			{"CascadePolicySet", PsCascadePolicySet},
			{"PolicyList", PsPolicyList},
			{"CascadeStatusGet", PsCascadeStatusGet},
			{"CascadeRename", PsCascadeRename},
			{"CascadeOnline", PsCascadeOnline},
			{"CascadeOffline", PsCascadeOffline},
			{"AccessAdd", PsAccessAdd},
			{"AccessAddEx", PsAccessAddEx},
			{"AccessAdd6", PsAccessAdd6},
			{"AccessAddEx6", PsAccessAddEx6},
			{"AccessList", PsAccessList},
			{"AccessDelete", PsAccessDelete},
			{"AccessEnable", PsAccessEnable},
			{"AccessDisable", PsAccessDisable},
			{"UserList", PsUserList},
			{"UserCreate", PsUserCreate},
			{"UserSet", PsUserSet},
			{"UserDelete", PsUserDelete},
			{"UserGet", PsUserGet},
			{"UserAnonymousSet", PsUserAnonymousSet},
			{"UserPasswordSet", PsUserPasswordSet},
			{"UserCertSet", PsUserCertSet},
			{"UserCertGet", PsUserCertGet},
			{"UserSignedSet", PsUserSignedSet},
			{"UserRadiusSet", PsUserRadiusSet},
			{"UserNTLMSet", PsUserNTLMSet},
			{"UserPolicyRemove", PsUserPolicyRemove},
			{"UserPolicySet", PsUserPolicySet},
			{"UserExpiresSet", PsUserExpiresSet},
			{"GroupList", PsGroupList},
			{"GroupCreate", PsGroupCreate},
			{"GroupSet", PsGroupSet},
			{"GroupDelete", PsGroupDelete},
			{"GroupGet", PsGroupGet},
			{"GroupJoin", PsGroupJoin},
			{"GroupUnjoin", PsGroupUnjoin},
			{"GroupPolicyRemove", PsGroupPolicyRemove},
			{"GroupPolicySet", PsGroupPolicySet},
			{"SessionList", PsSessionList},
			{"SessionGet", PsSessionGet},
			{"SessionDisconnect", PsSessionDisconnect},
			{"MacTable", PsMacTable},
			{"MacDelete", PsMacDelete},
			{"IpTable", PsIpTable},
			{"IpDelete", PsIpDelete},
			{"SecureNatEnable", PsSecureNatEnable},
			{"SecureNatDisable", PsSecureNatDisable},
			{"SecureNatStatusGet", PsSecureNatStatusGet},
			{"SecureNatHostGet", PsSecureNatHostGet},
			{"SecureNatHostSet", PsSecureNatHostSet},
			{"NatGet", PsNatGet},
			{"NatEnable", PsNatEnable},
			{"NatDisable", PsNatDisable},
			{"NatSet", PsNatSet},
			{"NatTable", PsNatTable},
			{"DhcpGet", PsDhcpGet},
			{"DhcpEnable", PsDhcpEnable},
			{"DhcpDisable", PsDhcpDisable},
			{"DhcpSet", PsDhcpSet},
			{"DhcpTable", PsDhcpTable},
			{"AdminOptionList", PsAdminOptionList},
			{"AdminOptionSet", PsAdminOptionSet},
			{"ExtOptionList", PsExtOptionList},
			{"ExtOptionSet", PsExtOptionSet},
			{"CrlList", PsCrlList},
			{"CrlAdd", PsCrlAdd},
			{"CrlDel", PsCrlDel},
			{"CrlGet", PsCrlGet},
			{"AcList", PsAcList},
			{"AcAdd", PsAcAdd},
			{"AcAdd6", PsAcAdd6},
			{"AcDel", PsAcDel},
			{"MakeCert", PtMakeCert},
			{"MakeCert2048", PtMakeCert2048},
			{"TrafficClient", PtTrafficClient},
			{"TrafficServer", PtTrafficServer},
			{"LicenseAdd", PsLicenseAdd},
			{"LicenseDel", PsLicenseDel},
			{"LicenseList", PsLicenseList},
			{"LicenseStatus", PsLicenseStatus},
			{"IPsecEnable", PsIPsecEnable},
			{"IPsecGet", PsIPsecGet},
			{"EtherIpClientAdd", PsEtherIpClientAdd},
			{"EtherIpClientDelete", PsEtherIpClientDelete},
			{"EtherIpClientList", PsEtherIpClientList},
			{"OpenVpnEnable", PsOpenVpnEnable},
			{"OpenVpnGet", PsOpenVpnGet},
			{"OpenVpnMakeConfig", PsOpenVpnMakeConfig},
			{"OpenVpnObfuscationEnable", PsOpenVpnObfuscationEnable},
			{"OpenVpnObfuscationGet", PsOpenVpnObfuscationGet},
			{"SstpEnable", PsSstpEnable},
			{"SstpGet", PsSstpGet},
			{"ServerCertRegenerate", PsServerCertRegenerate},
			{"VpnOverIcmpDnsEnable", PsVpnOverIcmpDnsEnable},
			{"VpnOverIcmpDnsGet", PsVpnOverIcmpDnsGet},
			{"DynamicDnsGetStatus", PsDynamicDnsGetStatus},
			{"DynamicDnsSetHostname", PsDynamicDnsSetHostname},
			{"VpnAzureGetStatus", PsVpnAzureGetStatus},
			{"VpnAzureSetEnable", PsVpnAzureSetEnable},
		};

		// Generate a prompt
		if (ps->HubName == NULL)
		{
			Format(prompt, sizeof(prompt), "VPN Server>");
		}
		else
		{
			Format(prompt, sizeof(prompt), "VPN Server/%s>", ps->HubName);
		}

		if (DispatchNextCmdEx(ps->Console, ps->CmdLine, prompt, cmd, sizeof(cmd) / sizeof(cmd[0]), ps) == false)
		{
			break;
		}
		ps->LastError = ps->Console->RetCode;

		if (ps->LastError == ERR_NO_ERROR && ps->Console->ConsoleType != CONSOLE_CSV)
		{
			ps->Console->Write(ps->Console, _UU("CMD_MSG_OK"));
			ps->Console->Write(ps->Console, L"");
		}

		if (ps->CmdLine != NULL)
		{
			break;
		}
	}

	// Release the Caps
	FreeCapsList(ps->CapsList);
	ps->CapsList = NULL;
}