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
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * sound; int /*<<< orphan*/  (* stop_cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ audio_mixer_voice_t ;
typedef  int /*<<< orphan*/  (* audio_mixer_stop_cb_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  audio_mixer_sound_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_MIXER_SOUND_STOPPED ; 
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_NONE ; 

void audio_mixer_stop(audio_mixer_voice_t* voice)
{
   audio_mixer_stop_cb_t stop_cb = NULL;
   audio_mixer_sound_t* sound    = NULL;

   if (voice)
   {
      stop_cb = voice->stop_cb;
      sound   = voice->sound;

      voice->type = AUDIO_MIXER_TYPE_NONE;

      if (stop_cb)
         stop_cb(sound, AUDIO_MIXER_SOUND_STOPPED);
   }
}