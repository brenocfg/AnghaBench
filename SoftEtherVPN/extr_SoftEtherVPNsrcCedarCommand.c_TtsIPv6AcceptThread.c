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
struct TYPE_3__ {int /*<<< orphan*/  ListenSocketV6; } ;
typedef  TYPE_1__ TTS ;
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  TtsAcceptProc (TYPE_1__*,int /*<<< orphan*/ ) ; 

void TtsIPv6AcceptThread(THREAD *thread, void *param)
{
	TTS *tts = (TTS *)param;
	// Validate arguments
	if (tts == NULL || param == NULL)
	{
		return;
	}

	TtsAcceptProc(tts, tts->ListenSocketV6);
}