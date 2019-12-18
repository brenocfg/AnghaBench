#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ bgm_volume; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASND_Init () ; 
 int /*<<< orphan*/  ASND_Pause (int /*<<< orphan*/ ) ; 
 scalar_t__ Bg_music_ogg ; 
 int /*<<< orphan*/  Bg_music_ogg_size ; 
 int /*<<< orphan*/  DSP_Unhalt () ; 
 int /*<<< orphan*/  OGG_INFINITE_TIME ; 
 int /*<<< orphan*/  PauseOgg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlayOgg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetVolumeOgg (int) ; 
 int /*<<< orphan*/  Shutdown ; 
 TYPE_1__ config ; 

void gx_audio_Stop(void)
{
  /* restart menu audio processing */
  DSP_Unhalt();
  ASND_Init();
  ASND_Pause(0);
	
  /* play background music */
  if (Bg_music_ogg && !Shutdown)
  {
    PauseOgg(0);	
    PlayOgg((char *)Bg_music_ogg, Bg_music_ogg_size, 0, OGG_INFINITE_TIME);	
    SetVolumeOgg(((int)config.bgm_volume * 255) / 100);	
  }
}