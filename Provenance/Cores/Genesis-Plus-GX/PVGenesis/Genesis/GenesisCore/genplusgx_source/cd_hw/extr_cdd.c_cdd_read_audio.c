#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int int16 ;
struct TYPE_16__ {int* ram; } ;
struct TYPE_12__ {TYPE_3__* tracks; } ;
struct TYPE_15__ {int* audio; size_t index; int volume; TYPE_4__ toc; } ;
struct TYPE_14__ {scalar_t__ datasource; } ;
struct TYPE_13__ {TYPE_2__* regs; } ;
struct TYPE_11__ {scalar_t__ fd; TYPE_6__ vf; } ;
struct TYPE_9__ {int /*<<< orphan*/  h; } ;
struct TYPE_10__ {int w; TYPE_1__ byte; } ;

/* Variables and functions */
 int /*<<< orphan*/ * blip ; 
 int /*<<< orphan*/  blip_add_delta_fast (int /*<<< orphan*/ ,int,int) ; 
 unsigned int blip_clocks_needed (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  blip_end_frame (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_8__ cdc ; 
 TYPE_7__ cdd ; 
 int /*<<< orphan*/  fread (int*,int,unsigned int,scalar_t__) ; 
 int ov_read (TYPE_6__*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_5__ scd ; 

void cdd_read_audio(unsigned int samples)
{
  /* previous audio outputs */
  int16 l = cdd.audio[0];
  int16 r = cdd.audio[1];

  /* get number of internal clocks (samples) needed */
  samples = blip_clocks_needed(blip[0], samples);

  /* audio track playing ? */
  if (!scd.regs[0x36>>1].byte.h && cdd.toc.tracks[cdd.index].fd)
  {
    int i, mul, delta;

    /* current CD-DA fader volume */
    int curVol = cdd.volume;

    /* CD-DA fader volume setup (0-1024) */
    int endVol = scd.regs[0x34>>1].w >> 4;

    /* read samples from current block */
#ifdef USE_LIBTREMOR
    if (cdd.toc.tracks[cdd.index].vf.datasource)
    {
      int len, done = 0;
      int16 *ptr = (int16 *) (cdc.ram);
      samples = samples * 4;
      while (done < samples)
      {
        len = ov_read(&cdd.toc.tracks[cdd.index].vf, (char *)(cdc.ram + done), samples - done, 0);
        if (len <= 0) 
        {
          done = samples;
          break;
        }
        done += len;
      }
      samples = done / 4;

      /* process 16-bit (host-endian) stereo samples */
      for (i=0; i<samples; i++)
      {
        /* CD-DA fader multiplier (cf. LC7883 datasheet) */
        /* (MIN) 0,1,2,3,4,8,12,16,20...,1020,1024 (MAX) */
        mul = (curVol & 0x7fc) ? (curVol & 0x7fc) : (curVol & 0x03);

        /* left channel */
        delta = ((ptr[0] * mul) / 1024) - l;
        ptr++;
        l += delta;
        blip_add_delta_fast(blip[0], i, delta);

        /* right channel */
        delta = ((ptr[0] * mul) / 1024) - r;
        ptr++;
        r += delta;
        blip_add_delta_fast(blip[1], i, delta);

        /* update CD-DA fader volume (one step/sample) */
        if (curVol < endVol)
        {
          /* fade-in */
          curVol++;
        }
        else if (curVol > endVol)
        {
          /* fade-out */
          curVol--;
        }
        else if (!curVol)
        {
          /* audio will remain muted until next setup */
          break;
        }
      }
    }
    else
#endif
    {
#ifdef LSB_FIRST
      int16 *ptr = (int16 *) (cdc.ram);
#else
      uint8 *ptr = cdc.ram;
#endif
      fread(cdc.ram, 1, samples * 4, cdd.toc.tracks[cdd.index].fd);

      /* process 16-bit (little-endian) stereo samples */
      for (i=0; i<samples; i++)
      {
        /* CD-DA fader multiplier (cf. LC7883 datasheet) */
        /* (MIN) 0,1,2,3,4,8,12,16,20...,1020,1024 (MAX) */
        mul = (curVol & 0x7fc) ? (curVol & 0x7fc) : (curVol & 0x03);

        /* left channel */
  #ifdef LSB_FIRST
        delta = ((ptr[0] * mul) / 1024) - l;
        ptr++;
  #else
        delta = (((int16)((ptr[0] + ptr[1]*256)) * mul) / 1024) - l;
        ptr += 2;
  #endif
        l += delta;
        blip_add_delta_fast(blip[0], i, delta);

        /* right channel */
  #ifdef LSB_FIRST
        delta = ((ptr[0] * mul) / 1024) - r;
        ptr++;
  #else
        delta = (((int16)((ptr[0] + ptr[1]*256)) * mul) / 1024) - r;
        ptr += 2;
  #endif
        r += delta;
        blip_add_delta_fast(blip[1], i, delta);

        /* update CD-DA fader volume (one step/sample) */
        if (curVol < endVol)
        {
          /* fade-in */
          curVol++;
        }
        else if (curVol > endVol)
        {
          /* fade-out */
          curVol--;
        }
        else if (!curVol)
        {
          /* audio will remain muted until next setup */
          break;
        }
      }
    }

    /* save current CD-DA fader volume */
    cdd.volume = curVol;

    /* save last audio output for next frame */
    cdd.audio[0] = l;
    cdd.audio[1] = r;
  }
  else
  {
    /* no audio output */
    if (l) blip_add_delta_fast(blip[0], 0, -l);
    if (r) blip_add_delta_fast(blip[1], 0, -r);

    /* save audio output for next frame */
    cdd.audio[0] = 0;
    cdd.audio[1] = 0;
  }

  /* end of Blip Buffer timeframe */
  blip_end_frame(blip[0], samples);
  blip_end_frame(blip[1], samples);
}