#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ASND_End () ; 
 int /*<<< orphan*/  ASND_Pause (int) ; 
 int /*<<< orphan*/  AUDIO_RegisterDMACallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUDIO_StopDMA () ; 
 int /*<<< orphan*/  DSP_Halt () ; 
 int /*<<< orphan*/  PauseOgg (int) ; 
 int SOUND_BUFFER_LEN ; 
 int /*<<< orphan*/  StopOgg () ; 
 int /*<<< orphan*/ * ai_callback ; 
 scalar_t__ audioStarted ; 
 scalar_t__ audio_sync ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mixbuffer ; 
 int /*<<< orphan*/  soundbuffer ; 

void gx_audio_Start(void)
{
  /* shutdown background music */
  PauseOgg(1);	
  StopOgg();	
  
  /* shutdown menu audio processing */
  ASND_Pause(1);
  ASND_End();
  AUDIO_StopDMA();
  AUDIO_RegisterDMACallback(NULL);
  DSP_Halt();

  /* DMA Interrupt callback */
  AUDIO_RegisterDMACallback(ai_callback);

  /* reset emulation audio processing */
  memset(soundbuffer, 0, 3 * SOUND_BUFFER_LEN);
  audioStarted = 0;
  mixbuffer = 0;
  audio_sync = 0;
}