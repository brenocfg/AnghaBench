#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hostname ;
struct TYPE_10__ {int Delay; int* CancelFlag; int Tcp_InNegotiation; int Ok; int Finished; int /*<<< orphan*/  FinishEvent; int /*<<< orphan*/  FinishedTick; TYPE_1__* Result_Tcp_Sock; int /*<<< orphan*/  CancelLock; TYPE_1__* CancelDisconnectSock; int /*<<< orphan*/  Hostname; scalar_t__ Tcp_TryStartSsl; int /*<<< orphan*/  Timeout; int /*<<< orphan*/  Port; int /*<<< orphan*/  Ip; } ;
struct TYPE_9__ {int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ CONNECT_TCP_RUDP_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 TYPE_1__* ConnectEx3 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int DetectIsServerSoftEtherVPN (TYPE_1__*) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int INFINITE ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimeout (TYPE_1__*,int) ; 
 int StartSSLEx (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitEx (int /*<<< orphan*/ *,int,int*) ; 

void ConnectThreadForTcp(THREAD *thread, void *param)
{
	SOCK *sock;
	char hostname[MAX_SIZE];
	CONNECT_TCP_RUDP_PARAM *p = (CONNECT_TCP_RUDP_PARAM *)param;
	if (thread == NULL || p == NULL)
	{
		return;
	}

	// Delay
	if (p->Delay >= 1)
	{
		WaitEx(NULL, p->Delay, p->CancelFlag);
	}

	// Connecting process
	IPToStr(hostname, sizeof(hostname), &p->Ip);
	sock = ConnectEx3(hostname, p->Port, p->Timeout, p->CancelFlag, NULL, NULL, false, true);

	if (sock != NULL && p->Tcp_TryStartSsl)
	{
		bool ssl_ret = false;

		p->Tcp_InNegotiation = true;

		// Attempt the SSL negotiation to take this opportunity
		Lock(p->CancelLock);
		{
			if ((*p->CancelFlag) == false)
			{
				p->CancelDisconnectSock = sock;
				AddRef(sock->ref);
			}
			else
			{
				Debug("User Cancel to StartSSL.\n");
				goto LABEL_CANCEL;
			}
		}
		Unlock(p->CancelLock);

		// Start the SSL communication
		ssl_ret = StartSSLEx(sock, NULL, NULL, 0, p->Hostname);

		if (ssl_ret)
		{
			// Identify whether the HTTPS server to be connected is a SoftEther VPN
			SetTimeout(sock, (10 * 1000));
			ssl_ret = DetectIsServerSoftEtherVPN(sock);
			SetTimeout(sock, INFINITE);

			if (ssl_ret == false)
			{
				Debug("DetectIsServerSoftEtherVPN Error.\n");
			}
		}

		Lock(p->CancelLock);
		{
			ReleaseSock(p->CancelDisconnectSock);
			p->CancelDisconnectSock = NULL;
		}
LABEL_CANCEL:
		Unlock(p->CancelLock);

		if (ssl_ret == false)
		{
			// SSL negotiation failure
			Disconnect(sock);
			ReleaseSock(sock);

			Debug("Fail to StartSSL.\n");

			sock = NULL;
		}
	}

	p->Result_Tcp_Sock = sock;
	p->Ok = (p->Result_Tcp_Sock == NULL ? false : true);
	p->FinishedTick = Tick64();
	p->Finished = true;
	p->Tcp_InNegotiation = false;

	Set(p->FinishEvent);
}