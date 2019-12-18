#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int numsamples; scalar_t__ samplerate; } ;
typedef  TYPE_3__ rwav_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum rwav_state { ____Placeholder_rwav_state } rwav_state ;
struct TYPE_9__ {unsigned int frames; float* pcm; } ;
struct TYPE_10__ {TYPE_1__ wav; } ;
struct TYPE_12__ {TYPE_2__ types; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ audio_mixer_sound_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_WAV ; 
 int RWAV_ITERATE_DONE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memalign_free (void*) ; 
 int /*<<< orphan*/  one_shot_resample (float*,size_t,scalar_t__,float**,size_t*) ; 
 int /*<<< orphan*/  rwav_free (TYPE_3__*) ; 
 int rwav_load (TYPE_3__*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ s_rate ; 
 int /*<<< orphan*/  wav2float (TYPE_3__*,float**,size_t) ; 

audio_mixer_sound_t* audio_mixer_load_wav(void *buffer, int32_t size)
{
   /* WAV data */
   rwav_t wav;
   /* WAV samples converted to float */
   float* pcm                 = NULL;
   size_t samples             = 0;
   /* Result */
   audio_mixer_sound_t* sound = NULL;
   enum rwav_state rwav_ret   = rwav_load(&wav, buffer, size);

   if (rwav_ret != RWAV_ITERATE_DONE)
      return NULL;

   samples       = wav.numsamples * 2;

   if (!wav2float(&wav, &pcm, samples))
      return NULL;

   if (wav.samplerate != s_rate)
   {
      float* resampled           = NULL;

      if (!one_shot_resample(pcm, samples,
               wav.samplerate, &resampled, &samples))
         return NULL;

      memalign_free((void*)pcm);
      pcm = resampled;
   }

   sound = (audio_mixer_sound_t*)calloc(1, sizeof(*sound));

   if (!sound)
   {
      memalign_free((void*)pcm);
      return NULL;
   }

   sound->type             = AUDIO_MIXER_TYPE_WAV;
   sound->types.wav.frames = (unsigned)(samples / 2);
   sound->types.wav.pcm    = pcm;

   rwav_free(&wav);

   return sound;
}