#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {int /*<<< orphan*/  ref; } ;
struct TYPE_13__ {int /*<<< orphan*/  SockEvent; int /*<<< orphan*/ * WorkThread; int /*<<< orphan*/  WorkerList; TYPE_5__* ListenSocketV6; TYPE_5__* ListenSocket; int /*<<< orphan*/  Print; int /*<<< orphan*/  Param; int /*<<< orphan*/ * IPv6AcceptThread; struct TYPE_13__* Tts; int /*<<< orphan*/  Port; int /*<<< orphan*/  ErrorCode; } ;
typedef  TYPE_1__ TTS_WORKER ;
typedef  TYPE_1__ TTS ;
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 scalar_t__ GetNumberOfCpu () ; 
 int /*<<< orphan*/  INFINITE ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_5__* ListenEx (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* ListenEx6 (int /*<<< orphan*/ ,int) ; 
 int MAX_SIZE ; 
 void* NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TtPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TtsAcceptProc (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  TtsIPv6AcceptThread ; 
 int /*<<< orphan*/  TtsWorkerThread ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

void TtsListenThread(THREAD *thread, void *param)
{
	TTS *tts;
	wchar_t tmp[MAX_SIZE];
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	tts = (TTS *)param;

	tts->ListenSocket = NULL;
	tts->ListenSocket = ListenEx(tts->Port, false);
	tts->ListenSocketV6 = ListenEx6(tts->Port, false);

	if (tts->ListenSocket == NULL && tts->ListenSocketV6 == NULL)
	{
		// Failed to Listen
		UniFormat(tmp, sizeof(tmp), _UU("TT_LISTEN_FAILED"), tts->Port);
		TtPrint(tts->Param, tts->Print, tmp);

		// Notify completion of preparation to parent thread
		NoticeThreadInit(thread);

		tts->ErrorCode = ERR_INTERNAL_ERROR;
	}
	else
	{
		UINT i, num_worker_threads;

		UniFormat(tmp, sizeof(tmp), _UU("TTS_LISTEN_STARTED"), tts->Port);
		TtPrint(tts->Param, tts->Print, tmp);

		if (tts->ListenSocketV6 != NULL)
		{
			UniFormat(tmp, sizeof(tmp), _UU("TTS_LISTEN_STARTED_V6"), tts->Port);
			TtPrint(tts->Param, tts->Print, tmp);
		}
		else
		{
			UniFormat(tmp, sizeof(tmp), _UU("TTS_LISTEN_FAILED_V6"), tts->Port);
			TtPrint(tts->Param, tts->Print, tmp);
		}

		if (tts->ListenSocket != NULL)
		{
			AddRef(tts->ListenSocket->ref);
		}
		if (tts->ListenSocketV6 != NULL)
		{
			AddRef(tts->ListenSocketV6->ref);
		}

		num_worker_threads = GetNumberOfCpu();

		// Start the worker threads
		for (i = 0;i < num_worker_threads;i++)
		{
			TTS_WORKER *w = ZeroMalloc(sizeof(TTS_WORKER));

			w->Tts = tts;
			w->WorkThread = NewThread(TtsWorkerThread, w);
			WaitThreadInit(w->WorkThread);

			Add(tts->WorkerList, w);
		}

		// Notify completion of preparation to parent thread
		NoticeThreadInit(thread);

		// Prepare for IPv6 Accept thread
		tts->IPv6AcceptThread = NULL;
		if (tts->ListenSocketV6 != NULL)
		{
			tts->IPv6AcceptThread = NewThread(TtsIPv6AcceptThread, tts);
		}

		TtsAcceptProc(tts, tts->ListenSocket);

		if (tts->IPv6AcceptThread != NULL)
		{
			WaitThread(tts->IPv6AcceptThread, INFINITE);
			ReleaseThread(tts->IPv6AcceptThread);
		}

		TtPrint(tts->Param, tts->Print, _UU("TTS_LISTEN_STOP"));

		ReleaseSock(tts->ListenSocket);
		ReleaseSock(tts->ListenSocketV6);

		for (i = 0;i < LIST_NUM(tts->WorkerList);i++)
		{
			TTS_WORKER *w = LIST_DATA(tts->WorkerList, i);

			SetSockEvent(w->SockEvent);

			// Wait for stopping the worker thread
			WaitThread(w->WorkThread, INFINITE);
			ReleaseThread(w->WorkThread);
			ReleaseSockEvent(w->SockEvent);

			Free(w);
		}
	}
}