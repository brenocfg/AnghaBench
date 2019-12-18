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
struct PicoVideo {int* reg; } ;
struct TYPE_2__ {int* vram; struct PicoVideo video; } ;

/* Variables and functions */
 int DrawScanline ; 
 scalar_t__ HighCol ; 
 int PDRAW_WND_DIFF_PRIO ; 
 TYPE_1__ Pico ; 
 int TileFlip (int,int,int) ; 
 int TileNorm (int,int,int) ; 
 int rendstatus ; 

__attribute__((used)) static void DrawWindow(int tstart, int tend, int prio, int sh) // int *hcache
{
  struct PicoVideo *pvid=&Pico.video;
  int tilex,ty,nametab,code=0;
  int blank=-1; // The tile we know is blank

  // Find name table line:
  if (pvid->reg[12]&1)
  {
    nametab=(pvid->reg[3]&0x3c)<<9; // 40-cell mode
    nametab+=(DrawScanline>>3)<<6;
  }
  else
  {
    nametab=(pvid->reg[3]&0x3e)<<9; // 32-cell mode
    nametab+=(DrawScanline>>3)<<5;
  }

  tilex=tstart<<1;

  if (!(rendstatus & PDRAW_WND_DIFF_PRIO)) {
    // check the first tile code
    code=Pico.vram[nametab+tilex];
    // if the whole window uses same priority (what is often the case), we may be able to skip this field
    if ((code>>15) != prio) return;
  }

  tend<<=1;
  ty=(DrawScanline&7)<<1; // Y-Offset into tile

  // Draw tiles across screen:
  if (!sh)
  {
    for (; tilex < tend; tilex++)
    {
      int addr=0,zero=0;
      int pal;

      code=Pico.vram[nametab+tilex];
      if (code==blank) continue;
      if ((code>>15) != prio) {
        rendstatus |= PDRAW_WND_DIFF_PRIO;
        continue;
      }

      pal=((code>>9)&0x30);

      // Get tile address/2:
      addr=(code&0x7ff)<<4;
      if (code&0x1000) addr+=14-ty; else addr+=ty; // Y-flip

      if (code&0x0800) zero=TileFlip(8+(tilex<<3),addr,pal);
      else             zero=TileNorm(8+(tilex<<3),addr,pal);

      if (zero) blank=code; // We know this tile is blank now
    }
  }
  else
  {
    for (; tilex < tend; tilex++)
    {
      int addr=0,zero=0;
      int pal;

      code=Pico.vram[nametab+tilex];
      if(code==blank) continue;
      if((code>>15) != prio) {
        rendstatus |= PDRAW_WND_DIFF_PRIO;
        continue;
      }

      pal=((code>>9)&0x30);

      if (prio) {
        int *zb = (int *)(HighCol+8+(tilex<<3));
        *zb++ &= 0xbfbfbfbf;
        *zb   &= 0xbfbfbfbf;
      } else {
        pal |= 0x40;
      }

      // Get tile address/2:
      addr=(code&0x7ff)<<4;
      if (code&0x1000) addr+=14-ty; else addr+=ty; // Y-flip

      if (code&0x0800) zero=TileFlip(8+(tilex<<3),addr,pal);
      else             zero=TileNorm(8+(tilex<<3),addr,pal);

      if (zero) blank=code; // We know this tile is blank now
    }
  }
}