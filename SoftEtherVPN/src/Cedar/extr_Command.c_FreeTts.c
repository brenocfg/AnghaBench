#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int Halt; int /*<<< orphan*/  WorkerList; int /*<<< orphan*/  ErrorCode; int /*<<< orphan*/  Print; int /*<<< orphan*/  Param; int /*<<< orphan*/  Thread; int /*<<< orphan*/  ListenSocketV6; int /*<<< orphan*/  ListenSocket; } ;
typedef  TYPE_1__ TTS ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TtPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT FreeTts(TTS *tts)
{
	UINT ret;
	// Validate arguments
	if (tts == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	TtPrint(tts->Param, tts->Print, _UU("TTS_STOP_INIT"));

	tts->Halt = true;
	Disconnect(tts->ListenSocket);
	ReleaseSock(tts->ListenSocket);
	Disconnect(tts->ListenSocketV6);
	ReleaseSock(tts->ListenSocketV6);

	// Wait for the termination of the thread
	WaitThread(tts->Thread, INFINITE);

	ReleaseThread(tts->Thread);

	TtPrint(tts->Param, tts->Print, _UU("TTS_STOP_FINISHED"));

	ret = tts->ErrorCode;

	ReleaseList(tts->WorkerList);

	Free(tts);

	return ret;
}