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
struct TYPE_10__ {int /*<<< orphan*/  ref; } ;
struct TYPE_9__ {int /*<<< orphan*/  Interrupt; void* SendQueue; void* RecvQueue; TYPE_2__* SockEvent; void* ServerPort; int /*<<< orphan*/  ServerIp; void* ClientPort; int /*<<< orphan*/  ClientIp; void* Now; int /*<<< orphan*/  TubeSend; int /*<<< orphan*/  TubeRecv; TYPE_3__* Cedar; int /*<<< orphan*/  ClientCipherName; int /*<<< orphan*/  ClientHostName; void* LastRecvTick; } ;
typedef  TYPE_1__ SSTP_SERVER ;
typedef  TYPE_2__ SOCK_EVENT ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NewInterruptManager () ; 
 void* NewQueueFast () ; 
 int /*<<< orphan*/  NewTubePair (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTubeSockEvent (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 void* Tick64 () ; 
 TYPE_1__* ZeroMalloc (int) ; 

SSTP_SERVER *NewSstpServer(CEDAR *cedar, IP *client_ip, UINT client_port, IP *server_ip,
						   UINT server_port, SOCK_EVENT *se,
						   char *client_host_name, char *crypt_name)
{
	SSTP_SERVER *s = ZeroMalloc(sizeof(SSTP_SERVER));

	s->LastRecvTick = Tick64();

	StrCpy(s->ClientHostName, sizeof(s->ClientHostName), client_host_name);
	StrCpy(s->ClientCipherName, sizeof(s->ClientCipherName), crypt_name);

	s->Cedar = cedar;
	AddRef(s->Cedar->ref);

	NewTubePair(&s->TubeSend, &s->TubeRecv, 0);
	SetTubeSockEvent(s->TubeSend, se);

	s->Now = Tick64();

	Copy(&s->ClientIp, client_ip, sizeof(IP));
	s->ClientPort = client_port;
	Copy(&s->ServerIp, server_ip, sizeof(IP));
	s->ServerPort = server_port;

	s->SockEvent = se;

	AddRef(s->SockEvent->ref);

	s->RecvQueue = NewQueueFast();
	s->SendQueue = NewQueueFast();

	s->Interrupt = NewInterruptManager();

	return s;
}