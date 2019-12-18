#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_23__ ;
typedef  struct TYPE_37__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  server_str ;
typedef  int /*<<< orphan*/  mschap_v2_server_response_20 ;
typedef  int /*<<< orphan*/  macstr ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_37__ {char* ClientProductName; char* ServerProductName; char* ClientOsName; char* ClientOsVer; char* ClientOsProductId; char* ClientHostname; char* HubName; int /*<<< orphan*/  ServerIpAddress6; int /*<<< orphan*/  ClientIpAddress6; int /*<<< orphan*/  UniqueId; void* ServerPort; void* ServerIpAddress; int /*<<< orphan*/  ServerHostname; void* ClientPort; void* ClientIpAddress; void* ServerProductBuild; void* ServerProductVer; void* ClientProductBuild; void* ClientProductVer; } ;
typedef  TYPE_1__ UCHAR ;
struct TYPE_43__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_42__ {scalar_t__ Version; scalar_t__ Build; int /*<<< orphan*/  ref; } ;
struct TYPE_41__ {int /*<<< orphan*/  Ref; } ;
struct TYPE_40__ {scalar_t__ Layer; char* ClientHostname; char* HubName; char* UserName; char* Password; int /*<<< orphan*/  IPv4ReceivedQueue; int /*<<< orphan*/  ArpTable; int /*<<< orphan*/  Interrupt; TYPE_2__* Sock; int /*<<< orphan*/  ConnectionName; int /*<<< orphan*/  SessionName; TYPE_1__* MacAddress; int /*<<< orphan*/  MsChapV2_ServerResponse; int /*<<< orphan*/  Policy; int /*<<< orphan*/  random; int /*<<< orphan*/  FlushList; TYPE_6__* Cedar; } ;
struct TYPE_38__ {TYPE_1__* ipv6_addr; } ;
struct TYPE_39__ {scalar_t__ LocalPort; scalar_t__ RemotePort; TYPE_23__ RemoteIP; TYPE_23__ LocalIP; } ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ NODE_INFO ;
typedef  TYPE_4__ IPC ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_5__ EAP_CLIENT ;
typedef  TYPE_6__ CEDAR ;
typedef  TYPE_7__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int ClientUploadSignature (TYPE_2__*) ; 
 TYPE_2__* ConnectInProc (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  Disconnect (TYPE_2__*) ; 
 scalar_t__ ERR_AUTH_FAILED ; 
 scalar_t__ ERR_DISCONNECTED ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_PROTOCOL_ERROR ; 
 void* Endian32 (scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_7__*) ; 
 int /*<<< orphan*/  FreeIPC (TYPE_4__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 scalar_t__ GetErrorFromPack (int /*<<< orphan*/ *) ; 
 int GetHello (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,char*,int) ; 
 TYPE_2__* GetInProcListeningSock (TYPE_6__*) ; 
 int /*<<< orphan*/ * HttpClientRecv (TYPE_2__*) ; 
 int HttpClientSend (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPCCmpArpTable ; 
 scalar_t__ IPC_LAYER_2 ; 
 int /*<<< orphan*/  IPToStr (int /*<<< orphan*/ ,int,TYPE_23__*) ; 
 void* IPToUINT (TYPE_23__*) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 scalar_t__ IsIP6 (TYPE_23__*) ; 
 scalar_t__ IsZero (TYPE_1__*,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MacToStr (char*,int,TYPE_1__*) ; 
 TYPE_7__* NewBuf () ; 
 int /*<<< orphan*/  NewInterruptManager () ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewQueue () ; 
 int /*<<< orphan*/  NewTubeFlushList () ; 
 int /*<<< orphan*/  OutRpcNodeInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  PackAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int PackGetData2 (int /*<<< orphan*/ *,char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/ * PackLoginWithOpenVPNCertificate (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackLoginWithPlainPassword (char*,char*,char*) ; 
 int ParseWelcomeFromPack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_2__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_7__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufStr (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_4__* ZeroMalloc (int) ; 

IPC *NewIPC(CEDAR *cedar, char *client_name, char *postfix, char *hubname, char *username, char *password,
			UINT *error_code, IP *client_ip, UINT client_port, IP *server_ip, UINT server_port,
			char *client_hostname, char *crypt_name,
			bool bridge_mode, UINT mss, EAP_CLIENT *eap_client, X *client_certificate,
			UINT layer)
{
	IPC *ipc;
	UINT dummy_int = 0;
	SOCK *a;
	SOCK *s;
	PACK *p;
	UINT err = ERR_INTERNAL_ERROR;
	char server_str[MAX_SIZE];
	char macstr[30];
	UINT server_ver, server_build;
	UCHAR unique[SHA1_SIZE];
	NODE_INFO info;
	BUF *b;
	UCHAR mschap_v2_server_response_20[20];
	// Validate arguments
	if (cedar == NULL || username == NULL || password == NULL || client_hostname == NULL)
	{
		return NULL;
	}
	if (IsEmptyStr(client_name))
	{
		client_name = "InProc VPN Connection";
	}
	if (IsEmptyStr(crypt_name))
	{
		crypt_name = "";
	}
	if (error_code == NULL)
	{
		error_code = &dummy_int;
	}

	Zero(mschap_v2_server_response_20, sizeof(mschap_v2_server_response_20));

	err = *error_code = ERR_INTERNAL_ERROR;

	a = GetInProcListeningSock(cedar);
	if (a == NULL)
	{
		return NULL;
	}

	ipc = ZeroMalloc(sizeof(IPC));

	ipc->Cedar = cedar;
	AddRef(cedar->ref);

	ipc->Layer = layer;
	if (ipc->Layer == 0)
	{
		ipc->Layer = IPC_LAYER_2;
	}

	ipc->FlushList = NewTubeFlushList();

	StrCpy(ipc->ClientHostname, sizeof(ipc->ClientHostname), client_hostname);
	StrCpy(ipc->HubName, sizeof(ipc->HubName), hubname);
	StrCpy(ipc->UserName, sizeof(ipc->UserName), username);
	StrCpy(ipc->Password, sizeof(ipc->Password), password);

	// Connect the in-process socket
	s = ConnectInProc(a, client_ip, client_port, server_ip, server_port);
	if (s == NULL)
	{
		goto LABEL_ERROR;
	}

	// Protocol initialization process
	if (ClientUploadSignature(s) == false)
	{
		err = ERR_DISCONNECTED;
		goto LABEL_ERROR;
	}

	p = HttpClientRecv(s);
	if (p == NULL)
	{
		err = ERR_DISCONNECTED;
		goto LABEL_ERROR;
	}

	err = GetErrorFromPack(p);
	if (err != ERR_NO_ERROR)
	{
		FreePack(p);
		goto LABEL_ERROR;
	}

	if (GetHello(p, ipc->random, &server_ver, &server_build, server_str, sizeof(server_str)) == false)
	{
		FreePack(p);
		err = ERR_DISCONNECTED;
		goto LABEL_ERROR;
	}

	FreePack(p);

	// Upload the authentication data
	if (client_certificate != NULL)
	{
		p = PackLoginWithOpenVPNCertificate(hubname, username, client_certificate);
	}
	else
	{
		p = PackLoginWithPlainPassword(hubname, username, password);
	}

	if (p == NULL)
	{
		err = ERR_AUTH_FAILED;
		goto LABEL_ERROR;
	}

	PackAddStr(p, "hello", client_name);
	PackAddInt(p, "client_ver", cedar->Version);
	PackAddInt(p, "client_build", cedar->Build);
	PackAddInt(p, "max_connection", 1);
	PackAddInt(p, "use_encrypt", 0);
	PackAddInt(p, "use_compress", 0);
	PackAddInt(p, "half_connection", 0);
	PackAddInt(p, "adjust_mss", mss);
	PackAddBool(p, "require_bridge_routing_mode", bridge_mode);
	PackAddBool(p, "require_monitor_mode", false);
	PackAddBool(p, "qos", false);

	if (eap_client != NULL)
	{
		UINT64 ptr = (UINT64)eap_client;
		PackAddInt64(p, "release_me_eap_client", ptr);

		AddRef(eap_client->Ref);
	}

	// Unique ID is determined by the sum of the connecting client IP address and the client_name
	b = NewBuf();
	WriteBuf(b, client_ip, sizeof(IP));
	WriteBufStr(b, client_name);
	WriteBufStr(b, crypt_name);

	Sha1(unique, b->Buf, b->Size);

	FreeBuf(b);

	PackAddData(p, "unique_id", unique, SHA1_SIZE);

	PackAddStr(p, "inproc_postfix", postfix);
	PackAddStr(p, "inproc_cryptname", crypt_name);
	PackAddInt(p, "inproc_layer", ipc->Layer);

	// Node information
	Zero(&info, sizeof(info));
	StrCpy(info.ClientProductName, sizeof(info.ClientProductName), client_name);
	info.ClientProductVer = Endian32(cedar->Version);
	info.ClientProductBuild = Endian32(cedar->Build);
	StrCpy(info.ServerProductName, sizeof(info.ServerProductName), server_str);
	info.ServerProductVer = Endian32(server_ver);
	info.ServerProductBuild = Endian32(server_build);
	StrCpy(info.ClientOsName, sizeof(info.ClientOsName), client_name);
	StrCpy(info.ClientOsVer, sizeof(info.ClientOsVer), "-");
	StrCpy(info.ClientOsProductId, sizeof(info.ClientOsProductId), "-");
	info.ClientIpAddress = IPToUINT(&s->LocalIP);
	info.ClientPort = Endian32(s->LocalPort);
	StrCpy(info.ClientHostname, sizeof(info.ClientHostname), ipc->ClientHostname);
	IPToStr(info.ServerHostname, sizeof(info.ServerHostname), &s->RemoteIP);
	info.ServerIpAddress = IPToUINT(&s->RemoteIP);
	info.ServerPort = Endian32(s->RemotePort);
	StrCpy(info.HubName, sizeof(info.HubName), hubname);
	Copy(info.UniqueId, unique, 16);
	if (IsIP6(&s->LocalIP))
	{
		Copy(info.ClientIpAddress6, s->LocalIP.ipv6_addr, 16);
	}
	if (IsIP6(&s->RemoteIP))
	{
		Copy(info.ServerIpAddress6, s->RemoteIP.ipv6_addr, 16);
	}
	OutRpcNodeInfo(p, &info);

	if (HttpClientSend(s, p) == false)
	{
		FreePack(p);
		err = ERR_DISCONNECTED;
		goto LABEL_ERROR;
	}

	FreePack(p);

	// Receive a Welcome packet
	p = HttpClientRecv(s);
	if (p == NULL)
	{
		err = ERR_DISCONNECTED;
		goto LABEL_ERROR;
	}

	err = GetErrorFromPack(p);
	if (err != ERR_NO_ERROR)
	{
		FreePack(p);
		goto LABEL_ERROR;
	}

	if (ParseWelcomeFromPack(p, ipc->SessionName, sizeof(ipc->SessionName),
		ipc->ConnectionName, sizeof(ipc->ConnectionName), &ipc->Policy) == false)
	{
		err = ERR_PROTOCOL_ERROR;
		FreePack(p);
		goto LABEL_ERROR;
	}

	if (PackGetData2(p, "IpcMacAddress", ipc->MacAddress, 6) == false || IsZero(ipc->MacAddress, 6))
	{
		err = ERR_PROTOCOL_ERROR;
		FreePack(p);
		goto LABEL_ERROR;
	}

	if (PackGetData2(p, "IpcMsChapV2ServerResponse", mschap_v2_server_response_20, sizeof(mschap_v2_server_response_20)))
	{
		Copy(ipc->MsChapV2_ServerResponse, mschap_v2_server_response_20, sizeof(mschap_v2_server_response_20));
	}

	PackGetStr(p, "IpcHubName", ipc->HubName, sizeof(ipc->HubName));
	Debug("IPC Hub Name: %s\n", ipc->HubName);

	MacToStr(macstr, sizeof(macstr), ipc->MacAddress);

	Debug("IPC: Session = %s, Connection = %s, Mac = %s\n", ipc->SessionName, ipc->ConnectionName, macstr);

	FreePack(p);

	ReleaseSock(a);
	ipc->Sock = s;

	Debug("NewIPC() Succeed.\n");

	ipc->Interrupt = NewInterruptManager();

	// Create an ARP table
	ipc->ArpTable = NewList(IPCCmpArpTable);

	// Create an IPv4 reception queue
	ipc->IPv4ReceivedQueue = NewQueue();

	return ipc;

LABEL_ERROR:
	Debug("NewIPC() Failed: Err = %u\n", err);
	Disconnect(s);
	ReleaseSock(s);
	ReleaseSock(a);
	FreeIPC(ipc);
	*error_code = err;
	return NULL;
}