#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT ;
struct TYPE_11__ {int /*<<< orphan*/  ref; } ;
struct TYPE_10__ {int EnableMSCHAPv2; int MsChapV2_ErrorCode; int /*<<< orphan*/  FlushList; int /*<<< orphan*/  ClientHostname; int /*<<< orphan*/  ClientSoftwareName; int /*<<< orphan*/  Postfix; TYPE_1__* TubeSend; TYPE_1__* TubeRecv; void* ServerPort; int /*<<< orphan*/  ServerIP; void* ClientPort; int /*<<< orphan*/  ClientIP; int /*<<< orphan*/  CryptName; void* AdjustMss; TYPE_3__* Cedar; int /*<<< orphan*/  AuthProtocol; } ;
struct TYPE_9__ {int /*<<< orphan*/  Ref; } ;
typedef  TYPE_1__ TUBE ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ PPP_SESSION ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPToStr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  NewTubeFlushList () ; 
 int /*<<< orphan*/  PPPThread ; 
 int /*<<< orphan*/  PPP_PROTOCOL_PAP ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_2__* ZeroMalloc (int) ; 

THREAD *NewPPPSession(CEDAR *cedar, IP *client_ip, UINT client_port, IP *server_ip, UINT server_port, TUBE *send_tube, TUBE *recv_tube, char *postfix, char *client_software_name, char *client_hostname, char *crypt_name, UINT adjust_mss)
{
	PPP_SESSION *p;
	THREAD *t;
	// Validate arguments
	if (cedar == NULL || client_ip == NULL || server_ip == NULL || send_tube == NULL || recv_tube == NULL)
	{
		return NULL;
	}
	if (IsEmptyStr(postfix))
	{
		postfix = "PPP";
	}
	if (IsEmptyStr(crypt_name))
	{
		crypt_name = "";
	}
	if (IsEmptyStr(client_software_name))
	{
		client_software_name = "PPP VPN Client";
	}

	// Data structure initialization
	p = ZeroMalloc(sizeof(PPP_SESSION));

	p->EnableMSCHAPv2 = true;
	p->AuthProtocol = PPP_PROTOCOL_PAP;
	p->MsChapV2_ErrorCode = 691;

	p->Cedar = cedar;
	AddRef(cedar->ref);

	p->AdjustMss = adjust_mss;

	StrCpy(p->CryptName, sizeof(p->CryptName), crypt_name);

	Copy(&p->ClientIP, client_ip, sizeof(IP));
	p->ClientPort = client_port;

	Copy(&p->ServerIP, server_ip, sizeof(IP));
	p->ServerPort = server_port;

	p->TubeRecv = recv_tube;
	p->TubeSend = send_tube;

	AddRef(p->TubeRecv->Ref);
	AddRef(p->TubeSend->Ref);

	StrCpy(p->Postfix, sizeof(p->Postfix), postfix);
	StrCpy(p->ClientSoftwareName, sizeof(p->ClientSoftwareName), client_software_name);

	if (IsEmptyStr(client_hostname))
	{
		IPToStr(p->ClientHostname, sizeof(p->ClientHostname), client_ip);
	}
	else
	{
		StrCpy(p->ClientHostname, sizeof(p->ClientHostname), client_hostname);
	}

	p->FlushList = NewTubeFlushList();

	// Thread creation
	t = NewThread(PPPThread, p);

	return t;
}