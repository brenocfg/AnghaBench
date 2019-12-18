#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int type; int repeat; float volume; int /*<<< orphan*/  stop_cb; TYPE_2__* sound; } ;
typedef  TYPE_1__ audio_mixer_voice_t ;
typedef  int /*<<< orphan*/  audio_mixer_stop_cb_t ;
struct TYPE_17__ {int type; } ;
typedef  TYPE_2__ audio_mixer_sound_t ;

/* Variables and functions */
 unsigned int AUDIO_MIXER_MAX_VOICES ; 
#define  AUDIO_MIXER_TYPE_FLAC 133 
#define  AUDIO_MIXER_TYPE_MOD 132 
#define  AUDIO_MIXER_TYPE_MP3 131 
#define  AUDIO_MIXER_TYPE_NONE 130 
#define  AUDIO_MIXER_TYPE_OGG 129 
#define  AUDIO_MIXER_TYPE_WAV 128 
 int audio_mixer_play_flac (TYPE_2__*,TYPE_1__*,int,float,int /*<<< orphan*/ ) ; 
 int audio_mixer_play_mod (TYPE_2__*,TYPE_1__*,int,float,int /*<<< orphan*/ ) ; 
 int audio_mixer_play_mp3 (TYPE_2__*,TYPE_1__*,int,float,int /*<<< orphan*/ ) ; 
 int audio_mixer_play_ogg (TYPE_2__*,TYPE_1__*,int,float,int /*<<< orphan*/ ) ; 
 int audio_mixer_play_wav (TYPE_2__*,TYPE_1__*,int,float,int /*<<< orphan*/ ) ; 
 TYPE_1__* s_voices ; 

audio_mixer_voice_t* audio_mixer_play(audio_mixer_sound_t* sound, bool repeat,
      float volume, audio_mixer_stop_cb_t stop_cb)
{
   unsigned i;
   bool res                   = false;
   audio_mixer_voice_t* voice = s_voices;

   if (!sound)
      return NULL;

   for (i = 0; i < AUDIO_MIXER_MAX_VOICES; i++, voice++)
   {
      if (voice->type != AUDIO_MIXER_TYPE_NONE)
         continue;

      switch (sound->type)
      {
         case AUDIO_MIXER_TYPE_WAV:
            res = audio_mixer_play_wav(sound, voice, repeat, volume, stop_cb);
            break;
         case AUDIO_MIXER_TYPE_OGG:
#ifdef HAVE_STB_VORBIS
            res = audio_mixer_play_ogg(sound, voice, repeat, volume, stop_cb);
#endif
            break;
         case AUDIO_MIXER_TYPE_MOD:
#ifdef HAVE_IBXM
            res = audio_mixer_play_mod(sound, voice, repeat, volume, stop_cb);
#endif
            break;
         case AUDIO_MIXER_TYPE_FLAC:
#ifdef HAVE_DR_FLAC
            res = audio_mixer_play_flac(sound, voice, repeat, volume, stop_cb);
#endif
            break;
         case AUDIO_MIXER_TYPE_MP3:
#ifdef HAVE_DR_MP3
            res = audio_mixer_play_mp3(sound, voice, repeat, volume, stop_cb);
#endif
            break;
         case AUDIO_MIXER_TYPE_NONE:
            break;
      }

      break;
   }

   if (res)
   {
      voice->type     = sound->type;
      voice->repeat   = repeat;
      voice->volume   = volume;
      voice->sound    = sound;
      voice->stop_cb  = stop_cb;
   }
   else
      voice = NULL;

   return voice;
}