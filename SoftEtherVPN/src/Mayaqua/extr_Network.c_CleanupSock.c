#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ socket; int /*<<< orphan*/  disconnect_lock; int /*<<< orphan*/  ssl_lock; int /*<<< orphan*/  lock; struct TYPE_9__* WaitToUseCipher; struct TYPE_9__* CipherName; int /*<<< orphan*/ * LocalX; int /*<<< orphan*/ * RemoteX; int /*<<< orphan*/ * hAcceptEvent; struct TYPE_9__* RemoteHostname; int /*<<< orphan*/  SendBuf; int /*<<< orphan*/ * R_UDP_Stack; int /*<<< orphan*/ * InProcRecvFifo; int /*<<< orphan*/ * BulkRecvKey; int /*<<< orphan*/ * BulkSendKey; int /*<<< orphan*/ * BulkSendTube; int /*<<< orphan*/ * BulkRecvTube; int /*<<< orphan*/ * RecvTube; int /*<<< orphan*/ * SendTube; int /*<<< orphan*/ * ReverseAcceptEvent; int /*<<< orphan*/ * ReverseAcceptQueue; int /*<<< orphan*/ * InProcAcceptEvent; int /*<<< orphan*/ * InProcAcceptQueue; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeRUDP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 TYPE_1__* GetNext (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseFifo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSharedBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseTube (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TubeDisconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnixFreeAsyncSocket (TYPE_1__*) ; 
 int /*<<< orphan*/  Win32FreeAsyncSocket (TYPE_1__*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  num_tcp_connections ; 

void CleanupSock(SOCK *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

//	{Debug("CleanupSock: Disconnect() Called: %s %u\n", __FILE__, __LINE__);Disconnect(s);}
	Disconnect(s);

	if (s->InProcAcceptQueue != NULL)
	{
		while (true)
		{
			SOCK *ss = GetNext(s->InProcAcceptQueue);
			if (ss == NULL)
			{
				break;
			}

			Disconnect(ss);
			ReleaseSock(ss);
		}

		ReleaseQueue(s->InProcAcceptQueue);
	}

	if (s->InProcAcceptEvent != NULL)
	{
		ReleaseEvent(s->InProcAcceptEvent);
	}

	if (s->ReverseAcceptQueue != NULL)
	{
		while (true)
		{
			SOCK *ss = GetNext(s->ReverseAcceptQueue);
			if (ss == NULL)
			{
				break;
			}

			Disconnect(ss);
			ReleaseSock(ss);
		}

		ReleaseQueue(s->ReverseAcceptQueue);
	}

	if (s->ReverseAcceptEvent != NULL)
	{
		ReleaseEvent(s->ReverseAcceptEvent);
	}

	if (s->SendTube != NULL)
	{
		TubeDisconnect(s->SendTube);
		ReleaseTube(s->SendTube);
	}

	if (s->RecvTube != NULL)
	{
		TubeDisconnect(s->RecvTube);
		ReleaseTube(s->RecvTube);
	}

	if (s->BulkRecvTube != NULL)
	{
		TubeDisconnect(s->BulkRecvTube);
		ReleaseTube(s->BulkRecvTube);
	}

	if (s->BulkSendTube != NULL)
	{
		TubeDisconnect(s->BulkSendTube);
		ReleaseTube(s->BulkSendTube);
	}

	if (s->BulkSendKey != NULL)
	{
		ReleaseSharedBuffer(s->BulkSendKey);
	}

	if (s->BulkRecvKey != NULL)
	{
		ReleaseSharedBuffer(s->BulkRecvKey);
	}

	if (s->InProcRecvFifo != NULL)
	{
		ReleaseFifo(s->InProcRecvFifo);
	}

	if (s->R_UDP_Stack != NULL)
	{
		FreeRUDP(s->R_UDP_Stack);
	}

#ifdef	OS_WIN32
	Win32FreeAsyncSocket(s);
#else	// OS_WIN32
	UnixFreeAsyncSocket(s);
#endif	// OS_WIN32

	FreeBuf(s->SendBuf);
	if (s->socket != INVALID_SOCKET)
	{
#ifdef	OS_WIN32
		closesocket(s->socket);
#else	// OS_WIN32
		close(s->socket);
#endif	// OS_WIN32
	}
	Free(s->RemoteHostname);

#ifdef	OS_WIN32
	if (s->hAcceptEvent != NULL)
	{
		CloseHandle(s->hAcceptEvent);
	}
#endif	// OS_WIN32

	// Release the certificate
	if (s->RemoteX != NULL)
	{
		FreeX(s->RemoteX);
		s->RemoteX = NULL;
	}
	if (s->LocalX != NULL)
	{
		FreeX(s->LocalX);
		s->LocalX = NULL;
	}

	// Cipher algorithm name
	if (s->CipherName != NULL)
	{
		Free(s->CipherName);
		s->CipherName = NULL;
	}

	Free(s->WaitToUseCipher);
	DeleteLock(s->lock);
	DeleteLock(s->ssl_lock);
	DeleteLock(s->disconnect_lock);

	Dec(num_tcp_connections);

	Free(s);
}