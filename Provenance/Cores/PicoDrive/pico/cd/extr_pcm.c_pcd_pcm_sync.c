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
struct pcm_chan {int addr; int* regs; } ;
struct TYPE_3__ {unsigned int update_cycles; int enabled; int control; struct pcm_chan* ch; } ;
struct TYPE_4__ {int pcm_mixpos; int* pcm_mixbuf; int pcm_mixbuf_dirty; int* pcm_ram; TYPE_1__ pcm; scalar_t__ pcm_regs_dirty; } ;

/* Variables and functions */
 int PCM_MIXBUF_LEN ; 
 int PCM_STEP_SHIFT ; 
 TYPE_2__* Pico_mcd ; 

void pcd_pcm_sync(unsigned int to)
{
  unsigned int cycles = Pico_mcd->pcm.update_cycles;
  int mul_l, mul_r, inc, smp;
  struct pcm_chan *ch;
  unsigned int addr;
  int c, s, steps;
  int enabled;
  int *out;

  if ((int)(to - cycles) < 384)
    return;

  steps = (to - cycles) / 384;
  if (Pico_mcd->pcm_mixpos + steps > PCM_MIXBUF_LEN)
    // shouldn't happen, but occasionally does
    steps = PCM_MIXBUF_LEN - Pico_mcd->pcm_mixpos;

  // PCM disabled or all channels off
  enabled = Pico_mcd->pcm.enabled;
  if (!(Pico_mcd->pcm.control & 0x80))
    enabled = 0;
  if (!enabled && !Pico_mcd->pcm_regs_dirty)
    goto end;

  out = Pico_mcd->pcm_mixbuf + Pico_mcd->pcm_mixpos * 2;
  Pico_mcd->pcm_mixbuf_dirty = 1;
  Pico_mcd->pcm_regs_dirty = 0;

  for (c = 0; c < 8; c++)
  {
    ch = &Pico_mcd->pcm.ch[c];

    if (!(enabled & (1 << c))) {
      ch->addr = ch->regs[6] << (PCM_STEP_SHIFT + 8);
      continue; // channel disabled
    }

    addr = ch->addr;
    inc = *(unsigned short *)&ch->regs[2];
    mul_l = ((int)ch->regs[0] * (ch->regs[1] & 0xf)) >> (5+1); 
    mul_r = ((int)ch->regs[0] * (ch->regs[1] >>  4)) >> (5+1);

    for (s = 0; s < steps; s++, addr = (addr + inc) & 0x7FFFFFF)
    {
      smp = Pico_mcd->pcm_ram[addr >> PCM_STEP_SHIFT];

      // test for loop signal
      if (smp == 0xff)
      {
        addr = *(unsigned short *)&ch->regs[4]; // loop_addr
        smp = Pico_mcd->pcm_ram[addr];
        addr <<= PCM_STEP_SHIFT;
        if (smp == 0xff)
          break;
      }

      if (smp & 0x80)
        smp = -(smp & 0x7f);

      out[s*2  ] += smp * mul_l; // max 128 * 119 = 15232
      out[s*2+1] += smp * mul_r;
    }
    ch->addr = addr;
  }

end:
  Pico_mcd->pcm.update_cycles = cycles + steps * 384;
  Pico_mcd->pcm_mixpos += steps;
}