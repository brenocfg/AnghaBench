#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int int32 ;
typedef  int int16 ;
struct TYPE_4__ {int filter; int lp_range; scalar_t__ mono; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** blips; } ;

/* Variables and functions */
 int ALIGN_SND ; 
 scalar_t__ SYSTEM_MCD ; 
 int /*<<< orphan*/  blip_mix_samples (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  blip_read_samples (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  cdd_read_audio (int) ; 
 TYPE_2__ config ; 
 int do_3band (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eq ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int llp ; 
 int /*<<< orphan*/  mcycles_vdp ; 
 int /*<<< orphan*/  pcm_update (int) ; 
 int rrp ; 
 TYPE_1__ snd ; 
 int sound_update (int /*<<< orphan*/ ) ; 
 scalar_t__ system_hw ; 

int audio_update(int16 *buffer)
{
  /* run sound chips until end of frame */
  int size = sound_update(mcycles_vdp);

  /* Mega CD specific */
  if (system_hw == SYSTEM_MCD)
  {
    /* sync PCM chip with other sound chips */
    pcm_update(size);

    /* read CDDA samples */
    cdd_read_audio(size);
  }

#ifdef ALIGN_SND
  /* return an aligned number of samples if required */
  size &= ALIGN_SND;
#endif

  /* resample FM & PSG mixed stream to output buffer */
#ifdef LSB_FIRST
  blip_read_samples(snd.blips[0][0], buffer, size);
  blip_read_samples(snd.blips[0][1], buffer + 1, size);
#else
  blip_read_samples(snd.blips[0][0], buffer + 1, size);
  blip_read_samples(snd.blips[0][1], buffer, size);
#endif

  /* Mega CD specific */
  if (system_hw == SYSTEM_MCD)
  {
    /* resample PCM & CD-DA streams to output buffer */
#ifdef LSB_FIRST
    blip_mix_samples(snd.blips[1][0], buffer, size);
    blip_mix_samples(snd.blips[1][1], buffer + 1, size);
    blip_mix_samples(snd.blips[2][0], buffer, size);
    blip_mix_samples(snd.blips[2][1], buffer + 1, size);
#else
    blip_mix_samples(snd.blips[1][0], buffer + 1, size);
    blip_mix_samples(snd.blips[1][1], buffer, size);
    blip_mix_samples(snd.blips[2][0], buffer + 1, size);
    blip_mix_samples(snd.blips[2][1], buffer, size);
#endif
  }

  /* Audio filtering */
  if (config.filter)
  {
    int samples = size;
    int16 *out = buffer;
    int32 l, r;

    if (config.filter & 1)
    {
      /* single-pole low-pass filter (6 dB/octave) */
      uint32 factora  = config.lp_range;
      uint32 factorb  = 0x10000 - factora;

      /* restore previous sample */
      l = llp;
      r = rrp;

      do
      {
        /* apply low-pass filter */
        l = l*factora + out[0]*factorb;
        r = r*factora + out[1]*factorb;

        /* 16.16 fixed point */
        l >>= 16;
        r >>= 16;

        /* update sound buffer */
        *out++ = l;
        *out++ = r;
      }
      while (--samples);

      /* save last samples for next frame */
      llp = l;
      rrp = r;
    }
    else if (config.filter & 2)
    {
      do
      {
        /* 3 Band EQ */
        l = do_3band(&eq,out[0]);
        r = do_3band(&eq,out[1]);

        /* clipping (16-bit samples) */
        if (l > 32767) l = 32767;
        else if (l < -32768) l = -32768;
        if (r > 32767) r = 32767;
        else if (r < -32768) r = -32768;

        /* update sound buffer */
        *out++ = l;
        *out++ = r;
      }
      while (--samples);
    }
  }

  /* Mono output mixing */
  if (config.mono)
  {
    int16 out;
    int samples = size;
    do
    {
      out = (buffer[0] + buffer[1]) / 2;
      *buffer++ = out;
      *buffer++ = out;
    }
    while (--samples);
  }

#ifdef LOGSOUND
  error("%d samples returned\n\n",size);
#endif

  return size;
}