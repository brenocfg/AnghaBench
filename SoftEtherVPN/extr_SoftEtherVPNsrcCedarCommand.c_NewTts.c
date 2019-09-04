#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/ * Thread; int /*<<< orphan*/  WorkerList; int /*<<< orphan*/ * Print; void* Param; int /*<<< orphan*/  Port; } ;
typedef  int /*<<< orphan*/  TT_PRINT_PROC ;
typedef  TYPE_1__ TTS ;
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TtPrint (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TtsListenThread ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

TTS *NewTts(UINT port, void *param, TT_PRINT_PROC *print_proc)
{
	TTS *tts;
	THREAD *t;

	tts = ZeroMalloc(sizeof(TTS));
	tts->Port = port;
	tts->Param = param;
	tts->Print = print_proc;

	TtPrint(param, print_proc, _UU("TTS_INIT"));

	tts->WorkerList = NewList(NULL);

	// Creating a thread
	t = NewThread(TtsListenThread, tts);
	WaitThreadInit(t);

	tts->Thread = t;

	return tts;
}