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
 scalar_t__ Bg_music_ogg ; 
 int /*<<< orphan*/  PauseOgg (int) ; 
 int /*<<< orphan*/  StopOgg () ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

void gx_audio_Shutdown(void)
{
  PauseOgg(1);
  StopOgg();
  ASND_Pause(1);
  ASND_End();
  if (Bg_music_ogg)
  {
    free(Bg_music_ogg);
  }
}