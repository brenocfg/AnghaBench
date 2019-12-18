#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
struct TYPE_16__ {int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteHostname; } ;
struct TYPE_15__ {int Halt; int /*<<< orphan*/  Print; int /*<<< orphan*/  Param; scalar_t__ IdSeed; int /*<<< orphan*/  WorkerList; } ;
struct TYPE_14__ {scalar_t__ Id; int /*<<< orphan*/  LastCommTime; scalar_t__ GiveupSpan; TYPE_4__* Sock; } ;
struct TYPE_13__ {int NewSocketArrived; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  TtsSockList; } ;
typedef  TYPE_1__ TTS_WORKER ;
typedef  TYPE_2__ TTS_SOCK ;
typedef  TYPE_3__ TTS ;
typedef  TYPE_4__ SOCK ;

/* Variables and functions */
 TYPE_4__* Accept (TYPE_4__*) ; 
 int /*<<< orphan*/  AcceptInitEx (TYPE_4__*,int) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  TtPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_2__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

void TtsAcceptProc(TTS *tts, SOCK *listen_socket)
{
	wchar_t tmp[MAX_SIZE];
	UINT seed = 0;
	// Validate arguments
	if (tts == NULL || listen_socket == NULL)
	{
		return;
	}

	while (tts->Halt == false)
	{
		SOCK *s;
		// Accept
		s = Accept(listen_socket);

		if (s == NULL)
		{
			if (tts->Halt == false)
			{
				SleepThread(10);
			}
			continue;
		}
		else
		{
			UINT num, i;
			TTS_WORKER *w;

			// Connected from the client
			AcceptInitEx(s, true);

			// Choose a worker thread
			num = LIST_NUM(tts->WorkerList);

			i = seed % num;

			seed++;

			w = LIST_DATA(tts->WorkerList, i);

			w->NewSocketArrived = true;
			LockList(w->TtsSockList);
			{
				TTS_SOCK *ts = ZeroMalloc(sizeof(TTS_SOCK));

				ts->Id = (++tts->IdSeed);
				ts->Sock = s;

				ts->GiveupSpan = (UINT64)(10 * 60 * 1000);
				ts->LastCommTime = Tick64();

				UniFormat(tmp, sizeof(tmp), _UU("TTS_ACCEPTED"), ts->Id,
					s->RemoteHostname, s->RemotePort);
				TtPrint(tts->Param, tts->Print, tmp);

				Insert(w->TtsSockList, ts);
				w->NewSocketArrived = true;
			}
			UnlockList(w->TtsSockList);

			SetSockEvent(w->SockEvent);
		}
	}
}