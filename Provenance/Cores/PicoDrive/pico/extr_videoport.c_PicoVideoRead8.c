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
struct TYPE_3__ {int status; int* reg; int pending_ints; unsigned int v_counter; int /*<<< orphan*/  pending; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_HVCNT ; 
 int /*<<< orphan*/  EL_SR ; 
 TYPE_2__ Pico ; 
 int SekCyclesDone () ; 
 int /*<<< orphan*/  SekPc ; 
 int VideoRead () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned int,int,...) ; 
 unsigned int* hcounts_32 ; 
 unsigned int* hcounts_40 ; 
 int line_base_cycles ; 

unsigned int PicoVideoRead8(unsigned int a)
{
  unsigned int d;
  a&=0x1d;

  switch (a)
  {
    case 0: return VideoRead() >> 8;
    case 1: return VideoRead() & 0xff;
    case 4: // control port/status reg
      d = Pico.video.status >> 8;
      if (d&1) Pico.video.status&=~0x100; // FIFO no longer full
      Pico.video.pending = 0;
      elprintf(EL_SR, "SR read (h): %02x @ %06x", d, SekPc);
      return d;
    case 5:
      d = Pico.video.status & 0xff;
      //if (PicoOpt&POPT_ALT_RENDERER) d|=0x0020; // sprite collision (Shadow of the Beast)
      d |= ((Pico.video.reg[1]&0x40)^0x40) >> 3;  // set V-Blank if display is disabled
      d |= (Pico.video.pending_ints&0x20)<<2;     // V-int pending?
      if (SekCyclesDone() - line_base_cycles >= 488-88) d |= 4;    // H-Blank
      Pico.video.pending = 0;
      elprintf(EL_SR, "SR read (l): %02x @ %06x", d, SekPc);
      return d;
    case 8: // hv counter
      elprintf(EL_HVCNT, "vcounter: %02x (%i) @ %06x", Pico.video.v_counter, SekCyclesDone(), SekPc);
      return Pico.video.v_counter;
    case 9:
      d = (SekCyclesDone() - line_base_cycles) & 0x1ff; // FIXME
      if (Pico.video.reg[12]&1)
           d = hcounts_40[d];
      else d = hcounts_32[d];
      elprintf(EL_HVCNT, "hcounter: %02x (%i) @ %06x", d, SekCyclesDone(), SekPc);
      return d;
  }

  return 0;
}