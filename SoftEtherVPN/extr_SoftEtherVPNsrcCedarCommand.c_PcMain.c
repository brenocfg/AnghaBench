#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  prompt ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_13__ {scalar_t__ RetCode; scalar_t__ ConsoleType; int /*<<< orphan*/  (* Write ) (TYPE_3__*,char*) ;} ;
struct TYPE_12__ {char* member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_11__ {scalar_t__ LastError; int /*<<< orphan*/ * CmdLine; TYPE_3__* Console; int /*<<< orphan*/  ServerName; } ;
typedef  TYPE_1__ PC ;
typedef  TYPE_2__ CMD ;

/* Variables and functions */
 scalar_t__ CONSOLE_CSV ; 
 int DispatchNextCmdEx (TYPE_3__*,int /*<<< orphan*/ *,char*,TYPE_2__*,int,TYPE_1__*) ; 
 scalar_t__ ERR_NO_ERROR ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  PcAccountAnonymousSet ; 
 int /*<<< orphan*/  PcAccountCertGet ; 
 int /*<<< orphan*/  PcAccountCertSet ; 
 int /*<<< orphan*/  PcAccountCompressDisable ; 
 int /*<<< orphan*/  PcAccountCompressEnable ; 
 int /*<<< orphan*/  PcAccountConnect ; 
 int /*<<< orphan*/  PcAccountCreate ; 
 int /*<<< orphan*/  PcAccountDelete ; 
 int /*<<< orphan*/  PcAccountDetailSet ; 
 int /*<<< orphan*/  PcAccountDisconnect ; 
 int /*<<< orphan*/  PcAccountEncryptDisable ; 
 int /*<<< orphan*/  PcAccountEncryptEnable ; 
 int /*<<< orphan*/  PcAccountExport ; 
 int /*<<< orphan*/  PcAccountGet ; 
 int /*<<< orphan*/  PcAccountHttpHeaderAdd ; 
 int /*<<< orphan*/  PcAccountHttpHeaderDelete ; 
 int /*<<< orphan*/  PcAccountHttpHeaderGet ; 
 int /*<<< orphan*/  PcAccountImport ; 
 int /*<<< orphan*/  PcAccountList ; 
 int /*<<< orphan*/  PcAccountNicSet ; 
 int /*<<< orphan*/  PcAccountPasswordSet ; 
 int /*<<< orphan*/  PcAccountProxyHttp ; 
 int /*<<< orphan*/  PcAccountProxyNone ; 
 int /*<<< orphan*/  PcAccountProxySocks ; 
 int /*<<< orphan*/  PcAccountProxySocks5 ; 
 int /*<<< orphan*/  PcAccountRename ; 
 int /*<<< orphan*/  PcAccountRetryOnServerCertDisable ; 
 int /*<<< orphan*/  PcAccountRetryOnServerCertEnable ; 
 int /*<<< orphan*/  PcAccountRetrySet ; 
 int /*<<< orphan*/  PcAccountSecureCertSet ; 
 int /*<<< orphan*/  PcAccountServerCertDelete ; 
 int /*<<< orphan*/  PcAccountServerCertDisable ; 
 int /*<<< orphan*/  PcAccountServerCertEnable ; 
 int /*<<< orphan*/  PcAccountServerCertGet ; 
 int /*<<< orphan*/  PcAccountServerCertSet ; 
 int /*<<< orphan*/  PcAccountSet ; 
 int /*<<< orphan*/  PcAccountStartupRemove ; 
 int /*<<< orphan*/  PcAccountStartupSet ; 
 int /*<<< orphan*/  PcAccountStatusGet ; 
 int /*<<< orphan*/  PcAccountStatusHide ; 
 int /*<<< orphan*/  PcAccountStatusShow ; 
 int /*<<< orphan*/  PcAccountUsernameSet ; 
 int /*<<< orphan*/  PcCertAdd ; 
 int /*<<< orphan*/  PcCertDelete ; 
 int /*<<< orphan*/  PcCertGet ; 
 int /*<<< orphan*/  PcCertList ; 
 int /*<<< orphan*/  PcKeepDisable ; 
 int /*<<< orphan*/  PcKeepEnable ; 
 int /*<<< orphan*/  PcKeepGet ; 
 int /*<<< orphan*/  PcKeepSet ; 
 int /*<<< orphan*/  PcNicCreate ; 
 int /*<<< orphan*/  PcNicDelete ; 
 int /*<<< orphan*/  PcNicDisable ; 
 int /*<<< orphan*/  PcNicEnable ; 
 int /*<<< orphan*/  PcNicGetSetting ; 
 int /*<<< orphan*/  PcNicList ; 
 int /*<<< orphan*/  PcNicSetSetting ; 
 int /*<<< orphan*/  PcNicUpgrade ; 
 int /*<<< orphan*/  PcPasswordGet ; 
 int /*<<< orphan*/  PcPasswordSet ; 
 int /*<<< orphan*/  PcRemoteDisable ; 
 int /*<<< orphan*/  PcRemoteEnable ; 
 int /*<<< orphan*/  PcSecureGet ; 
 int /*<<< orphan*/  PcSecureList ; 
 int /*<<< orphan*/  PcSecureSelect ; 
 int /*<<< orphan*/  PcTunDownOnDisconnectDisable ; 
 int /*<<< orphan*/  PcTunDownOnDisconnectEnable ; 
 int /*<<< orphan*/  PcTunDownOnDisconnectGet ; 
 int /*<<< orphan*/  PcVersionGet ; 
 int /*<<< orphan*/  PsAbout ; 
 int /*<<< orphan*/  PtCheck ; 
 int /*<<< orphan*/  PtMakeCert ; 
 int /*<<< orphan*/  PtMakeCert2048 ; 
 int /*<<< orphan*/  PtTrafficClient ; 
 int /*<<< orphan*/  PtTrafficServer ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,char*) ; 

void PcMain(PC *pc)
{
	char prompt[MAX_SIZE];
	wchar_t tmp[MAX_SIZE];
	// Validate arguments
	if (pc == NULL)
	{
		return;
	}

	// Display a message that the connection has been made
	UniFormat(tmp, sizeof(tmp), _UU("CMD_VPNCMD_CLIENT_CONNECTED"),
		pc->ServerName);
	pc->Console->Write(pc->Console, tmp);
	pc->Console->Write(pc->Console, L"");

	while (true)
	{
		// Definition of command
		CMD cmd[] =
		{
			{"About", PsAbout},
			{"Check", PtCheck},
			{"VersionGet", PcVersionGet},
			{"PasswordSet", PcPasswordSet},
			{"PasswordGet", PcPasswordGet},
			{"CertList", PcCertList},
			{"CertAdd", PcCertAdd},
			{"CertDelete", PcCertDelete},
			{"CertGet", PcCertGet},
			{"SecureList", PcSecureList},
			{"SecureSelect", PcSecureSelect},
			{"SecureGet", PcSecureGet},
			{"NicCreate", PcNicCreate},
			{"NicDelete", PcNicDelete},
			{"NicUpgrade", PcNicUpgrade},
			{"NicGetSetting", PcNicGetSetting},
			{"NicSetSetting", PcNicSetSetting},
			{"NicEnable", PcNicEnable},
			{"NicDisable", PcNicDisable},
			{"NicList", PcNicList},
			{"AccountList", PcAccountList},
			{"AccountCreate", PcAccountCreate},
			{"AccountSet", PcAccountSet},
			{"AccountGet", PcAccountGet},
			{"AccountDelete", PcAccountDelete},
			{"AccountUsernameSet", PcAccountUsernameSet},
			{"AccountAnonymousSet", PcAccountAnonymousSet},
			{"AccountPasswordSet", PcAccountPasswordSet},
			{"AccountCertSet", PcAccountCertSet},
			{"AccountCertGet", PcAccountCertGet},
			{"AccountEncryptDisable", PcAccountEncryptDisable},
			{"AccountEncryptEnable", PcAccountEncryptEnable},
			{"AccountCompressEnable", PcAccountCompressEnable},
			{"AccountCompressDisable", PcAccountCompressDisable},
			{"AccountHttpHeaderAdd", PcAccountHttpHeaderAdd},
			{"AccountHttpHeaderDelete", PcAccountHttpHeaderDelete},
			{"AccountHttpHeaderGet", PcAccountHttpHeaderGet},
			{"AccountProxyNone", PcAccountProxyNone},
			{"AccountProxyHttp", PcAccountProxyHttp},
			{"AccountProxySocks", PcAccountProxySocks},
			{"AccountProxySocks5", PcAccountProxySocks5},
			{"AccountServerCertEnable", PcAccountServerCertEnable},
			{"AccountServerCertDisable", PcAccountServerCertDisable},
			{"AccountRetryOnServerCertEnable", PcAccountRetryOnServerCertEnable},
			{"AccountRetryOnServerCertDisable", PcAccountRetryOnServerCertDisable},
			{"AccountServerCertSet", PcAccountServerCertSet},
			{"AccountServerCertDelete", PcAccountServerCertDelete},
			{"AccountServerCertGet", PcAccountServerCertGet},
			{"AccountDetailSet", PcAccountDetailSet},
			{"AccountRename", PcAccountRename},
			{"AccountConnect", PcAccountConnect},
			{"AccountDisconnect", PcAccountDisconnect},
			{"AccountStatusGet", PcAccountStatusGet},
			{"AccountNicSet", PcAccountNicSet},
			{"AccountStatusShow", PcAccountStatusShow},
			{"AccountStatusHide", PcAccountStatusHide},
			{"AccountSecureCertSet", PcAccountSecureCertSet},
			{"AccountRetrySet", PcAccountRetrySet},
			{"AccountStartupSet", PcAccountStartupSet},
			{"AccountStartupRemove", PcAccountStartupRemove},
			{"AccountExport", PcAccountExport},
			{"AccountImport", PcAccountImport},
			{"RemoteEnable", PcRemoteEnable},
			{"RemoteDisable", PcRemoteDisable},
			{"TUNDownOnDisconnectEnable", PcTunDownOnDisconnectEnable},
			{"TUNDownOnDisconnectDisable", PcTunDownOnDisconnectDisable},
			{"TUNDownOnDisconnectGet", PcTunDownOnDisconnectGet},
			{"KeepEnable", PcKeepEnable},
			{"KeepDisable", PcKeepDisable},
			{"KeepSet", PcKeepSet},
			{"KeepGet", PcKeepGet},
			{"MakeCert", PtMakeCert},
			{"MakeCert2048", PtMakeCert2048},
			{"TrafficClient", PtTrafficClient},
			{"TrafficServer", PtTrafficServer},
		};

		// Generate a prompt
		StrCpy(prompt, sizeof(prompt), "VPN Client>");

		if (DispatchNextCmdEx(pc->Console, pc->CmdLine, prompt, cmd, sizeof(cmd) / sizeof(cmd[0]), pc) == false)
		{
			break;
		}
		pc->LastError = pc->Console->RetCode;

		if (pc->LastError == ERR_NO_ERROR && pc->Console->ConsoleType != CONSOLE_CSV)
		{
			pc->Console->Write(pc->Console, _UU("CMD_MSG_OK"));
			pc->Console->Write(pc->Console, L"");
		}

		if (pc->CmdLine != NULL)
		{
			break;
		}
	}
}