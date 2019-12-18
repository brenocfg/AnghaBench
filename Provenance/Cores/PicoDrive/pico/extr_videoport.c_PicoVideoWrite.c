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
struct PicoVideo {int* reg; int pending; int command; int addr; int status; int lwrite_cnt; int type; int pending_ints; } ;
struct TYPE_3__ {int scanline; int dirtyPal; } ;
struct TYPE_4__ {unsigned short* vsram; TYPE_1__ m; struct PicoVideo video; } ;

/* Variables and functions */
 int /*<<< orphan*/  CommandChange () ; 
 int /*<<< orphan*/  DmaFill (unsigned short) ; 
 int /*<<< orphan*/  DrawSync (int) ; 
 int /*<<< orphan*/  EL_ANOMALY ; 
 int /*<<< orphan*/  EL_ASVDP ; 
 int /*<<< orphan*/  EL_INTSW ; 
 int /*<<< orphan*/  PDRAW_SPRITES_MOVED ; 
 int POPT_DIS_VDP_FIFO ; 
 TYPE_2__ Pico ; 
 int PicoOpt ; 
 int /*<<< orphan*/  SekCyclesBurnRun (int) ; 
 int SekCyclesDone () ; 
 int /*<<< orphan*/  SekEndRun (int) ; 
 int /*<<< orphan*/  SekInterrupt (int) ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  SekShouldInterrupt () ; 
 int /*<<< orphan*/  VideoWrite (unsigned short) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,unsigned short,int,...) ; 
 int line_base_cycles ; 
 int /*<<< orphan*/  rendstatus ; 

void PicoVideoWrite(unsigned int a,unsigned short d)
{
  struct PicoVideo *pvid=&Pico.video;

  //if (Pico.m.scanline < 224)
  //  elprintf(EL_STATUS, "PicoVideoWrite [%06x] %04x", a, d);
  a&=0x1c;

  if (a==0x00) // Data port 0 or 2
  {
    // try avoiding the sync..
    if (Pico.m.scanline < 224 && (pvid->reg[1]&0x40) &&
        !(!pvid->pending &&
          ((pvid->command & 0xc00000f0) == 0x40000010 && Pico.vsram[pvid->addr>>1] == d))
       )
      DrawSync(0);

    if (pvid->pending) {
      CommandChange();
      pvid->pending=0;
    }

    // If a DMA fill has been set up, do it
    if ((pvid->command&0x80) && (pvid->reg[1]&0x10) && (pvid->reg[0x17]>>6)==2)
    {
      DmaFill(d);
    }
    else
    {
      // preliminary FIFO emulation for Chaos Engine, The (E)
      if (!(pvid->status&8) && (pvid->reg[1]&0x40) && !(PicoOpt&POPT_DIS_VDP_FIFO)) // active display?
      {
        pvid->status&=~0x200; // FIFO no longer empty
        pvid->lwrite_cnt++;
        if (pvid->lwrite_cnt >= 4) pvid->status|=0x100; // FIFO full
        if (pvid->lwrite_cnt >  4) {
          SekCyclesBurnRun(32); // penalty // 488/12-8
        }
        elprintf(EL_ASVDP, "VDP data write: %04x [%06x] {%i} #%i @ %06x", d, Pico.video.addr,
                 Pico.video.type, pvid->lwrite_cnt, SekPc);
      }
      VideoWrite(d);
    }
    return;
  }

  if (a==0x04) // Control (command) port 4 or 6
  {
    if (pvid->pending)
    {
      if (d & 0x80) DrawSync(0); // only need sync for DMA
      // Low word of command:
      pvid->command&=0xffff0000;
      pvid->command|=d;
      pvid->pending=0;
      CommandChange();
    }
    else
    {
      if ((d&0xc000)==0x8000)
      {
        // Register write:
        int num=(d>>8)&0x1f;
        int dold=pvid->reg[num];
        int blank_on = 0;
        pvid->type=0; // register writes clear command (else no Sega logo in Golden Axe II)
        if (num > 0x0a && !(pvid->reg[1]&4)) {
          elprintf(EL_ANOMALY, "%02x written to reg %02x in SMS mode @ %06x", d, num, SekPc);
          return;
        }

        if (num == 1 && !(d&0x40) && SekCyclesDone() - line_base_cycles <= 488-390)
          blank_on = 1;
        DrawSync(blank_on);
        pvid->reg[num]=(unsigned char)d;
        switch (num)
        {
          case 0x00:
            elprintf(EL_INTSW, "hint_onoff: %i->%i [%i] pend=%i @ %06x", (dold&0x10)>>4,
                    (d&0x10)>>4, SekCyclesDone(), (pvid->pending_ints&0x10)>>4, SekPc);
            goto update_irq;
          case 0x01:
            elprintf(EL_INTSW, "vint_onoff: %i->%i [%i] pend=%i @ %06x", (dold&0x20)>>5,
                    (d&0x20)>>5, SekCyclesDone(), (pvid->pending_ints&0x20)>>5, SekPc);
            goto update_irq;
          case 0x05:
            //elprintf(EL_STATUS, "spritep moved to %04x", (unsigned)(Pico.video.reg[5]&0x7f) << 9);
            if (d^dold) rendstatus |= PDRAW_SPRITES_MOVED;
            break;
          case 0x0c:
            // renderers should update their palettes if sh/hi mode is changed
            if ((d^dold)&8) Pico.m.dirtyPal = 2;
            break;
        }
        return;

update_irq:
#ifndef EMU_CORE_DEBUG
        // update IRQ level
        if (!SekShouldInterrupt()) // hack
        {
          int lines, pints, irq=0;
          lines = (pvid->reg[1] & 0x20) | (pvid->reg[0] & 0x10);
          pints = (pvid->pending_ints&lines);
               if (pints & 0x20) irq = 6;
          else if (pints & 0x10) irq = 4;
          SekInterrupt(irq); // update line

          if (irq) SekEndRun(24); // make it delayed
        }
#endif
      }
      else
      {
        // High word of command:
        pvid->command&=0x0000ffff;
        pvid->command|=d<<16;
        pvid->pending=1;
      }
    }
  }
}