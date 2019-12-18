#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int cycles; int status; short* ram; int* out; TYPE_3__* chan; scalar_t__ enabled; } ;
struct TYPE_9__ {char* cycles; } ;
struct TYPE_7__ {scalar_t__ w; } ;
struct TYPE_6__ {int w; } ;
struct TYPE_8__ {int addr; short env; int pan; TYPE_2__ fd; TYPE_1__ ls; } ;

/* Variables and functions */
 unsigned int PCM_SCYCLES_RATIO ; 
 int /*<<< orphan*/ * blip ; 
 int /*<<< orphan*/  blip_add_delta_fast (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  blip_end_frame (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 TYPE_5__ pcm ; 
 TYPE_4__ s68k ; 
 int /*<<< orphan*/  v_counter ; 

void pcm_run(unsigned int length)
{
#ifdef LOG_PCM
  error("[%d][%d]run %d PCM samples (from %d)\n", v_counter, s68k.cycles, length, pcm.cycles);
#endif
  /* check if PCM chip is running */
  if (pcm.enabled)
  {
    int i, j, l, r;
  
    /* generate PCM samples */
    for (i=0; i<length; i++)
    {
      /* clear output */
      l = r = 0;

      /* run eight PCM channels */
      for (j=0; j<8; j++)
      {
        /* check if channel is enabled */
        if (pcm.status & (1 << j))
        {
          /* read from current WAVE RAM address */
          short data = pcm.ram[(pcm.chan[j].addr >> 11) & 0xffff];

          /* loop data ? */
          if (data == 0xff)
          {
            /* reset WAVE RAM address */
            pcm.chan[j].addr = pcm.chan[j].ls.w << 11;

            /* read again from WAVE RAM address */
            data = pcm.ram[pcm.chan[j].ls.w];
          }
          else
          {
            /* increment WAVE RAM address */
            pcm.chan[j].addr += pcm.chan[j].fd.w;
          }

          /* infinite loop should not output any data */
          if (data != 0xff)
          {
            /* check sign bit (output centered around 0) */
            if (data & 0x80)
            {
              /* PCM data is positive */
              data = data & 0x7f;
            }
            else
            {
              /* PCM data is negative */
              data = -(data & 0x7f);
            }

            /* multiply PCM data with ENV & stereo PAN data then add to L/R outputs (14.5 fixed point) */
            l += ((data * pcm.chan[j].env * (pcm.chan[j].pan & 0x0F)) >> 5);
            r += ((data * pcm.chan[j].env * (pcm.chan[j].pan >> 4)) >> 5);
          }
        }
      }

      /* limiter */
      if (l < -32768) l = -32768;
      else if (l > 32767) l = 32767;
      if (r < -32768) r = -32768;
      else if (r > 32767) r = 32767;

      /* check if PCM left output changed */
      if (pcm.out[0] != l)
      {
        blip_add_delta_fast(blip[0], i, l-pcm.out[0]);
        pcm.out[0] = l;
      }

      /* check if PCM right output changed */
      if (pcm.out[1] != r)
      {
        blip_add_delta_fast(blip[1], i, r-pcm.out[1]);
        pcm.out[1] = r;
      }
    }
  }
  else
  {
    /* check if PCM left output changed */
    if (pcm.out[0])
    {
      blip_add_delta_fast(blip[0], 0, -pcm.out[0]);
      pcm.out[0] = 0;
    }

    /* check if PCM right output changed */
    if (pcm.out[1])
    {
      blip_add_delta_fast(blip[1], 0, -pcm.out[1]);
      pcm.out[1] = 0;
    }
  }

  /* end of blip buffer frame */
  blip_end_frame(blip[0], length);
  blip_end_frame(blip[1], length);

  /* update PCM master clock counter */
  pcm.cycles += length * PCM_SCYCLES_RATIO;
}