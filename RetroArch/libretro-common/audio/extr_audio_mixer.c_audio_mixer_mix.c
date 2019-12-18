#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float volume; int type; } ;
typedef  TYPE_1__ audio_mixer_voice_t ;

/* Variables and functions */
 unsigned int AUDIO_MIXER_MAX_VOICES ; 
#define  AUDIO_MIXER_TYPE_FLAC 133 
#define  AUDIO_MIXER_TYPE_MOD 132 
#define  AUDIO_MIXER_TYPE_MP3 131 
#define  AUDIO_MIXER_TYPE_NONE 130 
#define  AUDIO_MIXER_TYPE_OGG 129 
#define  AUDIO_MIXER_TYPE_WAV 128 
 int /*<<< orphan*/  audio_mixer_mix_flac (float*,size_t,TYPE_1__*,float) ; 
 int /*<<< orphan*/  audio_mixer_mix_mod (float*,size_t,TYPE_1__*,float) ; 
 int /*<<< orphan*/  audio_mixer_mix_mp3 (float*,size_t,TYPE_1__*,float) ; 
 int /*<<< orphan*/  audio_mixer_mix_ogg (float*,size_t,TYPE_1__*,float) ; 
 int /*<<< orphan*/  audio_mixer_mix_wav (float*,size_t,TYPE_1__*,float) ; 
 TYPE_1__* s_voices ; 

void audio_mixer_mix(float* buffer, size_t num_frames, float volume_override, bool override)
{
   unsigned i;
   size_t j                   = 0;
   float* sample              = NULL;
   audio_mixer_voice_t* voice = s_voices;

   for (i = 0; i < AUDIO_MIXER_MAX_VOICES; i++, voice++)
   {
      float volume = (override) ? volume_override : voice->volume;

      switch (voice->type)
      {
         case AUDIO_MIXER_TYPE_WAV:
            audio_mixer_mix_wav(buffer, num_frames, voice, volume);
            break;
         case AUDIO_MIXER_TYPE_OGG:
#ifdef HAVE_STB_VORBIS
            audio_mixer_mix_ogg(buffer, num_frames, voice, volume);
#endif
            break;
         case AUDIO_MIXER_TYPE_MOD:
#ifdef HAVE_IBXM
            audio_mixer_mix_mod(buffer, num_frames, voice, volume);
#endif
            break;
         case AUDIO_MIXER_TYPE_FLAC:
#ifdef HAVE_DR_FLAC
            audio_mixer_mix_flac(buffer, num_frames, voice, volume);
#endif
            break;
            case AUDIO_MIXER_TYPE_MP3:
#ifdef HAVE_DR_MP3
            audio_mixer_mix_mp3(buffer, num_frames, voice, volume);
#endif
            break;
         case AUDIO_MIXER_TYPE_NONE:
            break;
      }
   }

   for (j = 0, sample = buffer; j < num_frames; j++, sample++)
   {
      if (*sample < -1.0f)
         *sample = -1.0f;
      else if (*sample > 1.0f)
         *sample = 1.0f;
   }
}