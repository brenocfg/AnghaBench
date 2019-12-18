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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_3__ {char* ClientProductName; char* ClientOsName; char* ClientOsVer; char* ClientOsProductId; char* ClientHostname; char* ServerHostname; char* ProxyHostname; int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyIpAddress6; int /*<<< orphan*/  ProxyIpAddress; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIpAddress6; int /*<<< orphan*/  ServerIpAddress; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIpAddress6; int /*<<< orphan*/  ClientIpAddress; int /*<<< orphan*/  ClientProductBuild; int /*<<< orphan*/  ClientProductVer; } ;
typedef  TYPE_1__ NODE_INFO ;
typedef  int /*<<< orphan*/  CT ;

/* Variables and functions */
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPToStr4or6 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int,...) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

void CmdPrintNodeInfo(CT *ct, NODE_INFO *info)
{
	wchar_t tmp[MAX_SIZE];
	char str[MAX_SIZE];
	// Validate arguments
	if (ct == NULL || info == NULL)
	{
		return;
	}

	StrToUni(tmp, sizeof(tmp), info->ClientProductName);
	CtInsert(ct, _UU("SM_NODE_CLIENT_NAME"), tmp);

	UniFormat(tmp, sizeof(tmp), L"%u.%02u", Endian32(info->ClientProductVer) / 100, Endian32(info->ClientProductVer) % 100);
	CtInsert(ct, _UU("SM_NODE_CLIENT_VER"), tmp);

	UniFormat(tmp, sizeof(tmp), L"Build %u", Endian32(info->ClientProductBuild));
	CtInsert(ct, _UU("SM_NODE_CLIENT_BUILD"), tmp);

	StrToUni(tmp, sizeof(tmp), info->ClientOsName);
	CtInsert(ct, _UU("SM_NODE_CLIENT_OS_NAME"), tmp);

	StrToUni(tmp, sizeof(tmp), info->ClientOsVer);
	CtInsert(ct, _UU("SM_NODE_CLIENT_OS_VER"), tmp);

	StrToUni(tmp, sizeof(tmp), info->ClientOsProductId);
	CtInsert(ct, _UU("SM_NODE_CLIENT_OS_PID"), tmp);

	StrToUni(tmp, sizeof(tmp), info->ClientHostname);
	CtInsert(ct, _UU("SM_NODE_CLIENT_HOST"), tmp);

	IPToStr4or6(str, sizeof(str), info->ClientIpAddress, info->ClientIpAddress6);
	StrToUni(tmp, sizeof(tmp), str);
	CtInsert(ct, _UU("SM_NODE_CLIENT_IP"), tmp);

	UniToStru(tmp, Endian32(info->ClientPort));
	CtInsert(ct, _UU("SM_NODE_CLIENT_PORT"), tmp);

	StrToUni(tmp, sizeof(tmp), info->ServerHostname);
	CtInsert(ct, _UU("SM_NODE_SERVER_HOST"), tmp);

	IPToStr4or6(str, sizeof(str), info->ServerIpAddress, info->ServerIpAddress6);
	StrToUni(tmp, sizeof(tmp), str);
	CtInsert(ct, _UU("SM_NODE_SERVER_IP"), tmp);

	UniToStru(tmp, Endian32(info->ServerPort));
	CtInsert(ct, _UU("SM_NODE_SERVER_PORT"), tmp);

	if (StrLen(info->ProxyHostname) != 0)
	{
		StrToUni(tmp, sizeof(tmp), info->ProxyHostname);
		CtInsert(ct, _UU("SM_NODE_PROXY_HOSTNAME"), tmp);

		IPToStr4or6(str, sizeof(str), info->ProxyIpAddress, info->ProxyIpAddress6);
		StrToUni(tmp, sizeof(tmp), str);
		CtInsert(ct, _UU("SM_NODE_PROXY_IP"), tmp);

		UniToStru(tmp, Endian32(info->ProxyPort));
		CtInsert(ct, _UU("SM_NODE_PROXY_PORT"), tmp);
	}
}