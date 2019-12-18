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
struct PicoVideo {unsigned int status; int* reg; int pending_ints; int v_counter; scalar_t__ pending; } ;
struct TYPE_2__ {struct PicoVideo video; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_HVCNT ; 
 int /*<<< orphan*/  EL_SR ; 
 TYPE_1__ Pico ; 
 int SekCyclesDone () ; 
 int /*<<< orphan*/  SekPc ; 
 unsigned int VideoRead () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned int,int,...) ; 
 unsigned int* hcounts_32 ; 
 unsigned int* hcounts_40 ; 
 int line_base_cycles ; 

unsigned int PicoVideoRead(unsigned int a)
{
  a&=0x1c;

  if (a==0x04) // control port
  {
    struct PicoVideo *pv=&Pico.video;
    unsigned int d;
    d=pv->status;
    //if (PicoOpt&POPT_ALT_RENDERER) d|=0x0020; // sprite collision (Shadow of the Beast)
    if (SekCyclesDone() - line_base_cycles >= 488-88)
      d|=0x0004; // H-Blank (Sonic3 vs)

    d |= ((pv->reg[1]&0x40)^0x40) >> 3;  // set V-Blank if display is disabled
    d |= (pv->pending_ints&0x20)<<2;     // V-int pending?
    if (d&0x100) pv->status&=~0x100; // FIFO no longer full

    pv->pending = 0; // ctrl port reads clear write-pending flag (Charles MacDonald)

    elprintf(EL_SR, "SR read: %04x @ %06x", d, SekPc);
    return d;
  }

  // H-counter info (based on Generator):
  // frame:
  //                       |       <- hblank? ->      |
  // start    <416>       hint  <36> hdisplay <38>  end // CPU cycles
  // |---------...---------|------------|-------------|
  // 0                   B6 E4                       FF // 40 cells
  // 0                   93 E8                       FF // 32 cells

  // Gens (?)              v-render
  // start  <hblank=84>   hint    hdisplay <404>      |
  // |---------------------|--------------------------|
  // E4  (hc[0x43]==0)    07                         B1 // 40
  // E8  (hc[0x45]==0)    05                         91 // 32

  // check: Sonic 3D Blast bonus, Cannon Fodder, Chase HQ II, 3 Ninjas kick back, Road Rash 3, Skitchin', Wheel of Fortune
  if ((a&0x1c)==0x08)
  {
    unsigned int d;

    d = (SekCyclesDone() - line_base_cycles) & 0x1ff; // FIXME
    if (Pico.video.reg[12]&1)
         d = hcounts_40[d];
    else d = hcounts_32[d];

    elprintf(EL_HVCNT, "hv: %02x %02x (%i) @ %06x", d, Pico.video.v_counter, SekCyclesDone(), SekPc);
    return d | (Pico.video.v_counter << 8);
  }

  if (a==0x00) // data port
  {
    return VideoRead();
  }

  return 0;
}