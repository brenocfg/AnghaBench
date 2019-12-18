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
struct TileStrip {int hscroll; int cells; int line; int nametab; int xmask; scalar_t__* hc; } ;
struct TYPE_2__ {int* vsram; int* vram; } ;

/* Variables and functions */
 int DrawScanline ; 
 int /*<<< orphan*/  PDRAW_PLANE_HI_PRIO ; 
 TYPE_1__ Pico ; 
 int TileFlip (int,int,int) ; 
 int TileNorm (int,int,int) ; 
 int /*<<< orphan*/  rendstatus ; 

void DrawStripVSRam(struct TileStrip *ts, int plane_sh, int cellskip)
{
  int tilex,dx,code=0,addr=0,cell=0;
  int oldcode=-1,blank=-1; // The tile we know is blank
  int pal=0,scan=DrawScanline;

  // Draw tiles across screen:
  tilex=(-ts->hscroll)>>3;
  dx=((ts->hscroll-1)&7)+1;
  if(dx != 8) cell--; // have hscroll, start with negative cell
  cell+=cellskip;
  tilex+=cellskip;
  dx+=cellskip<<3;

  for (; cell < ts->cells; dx+=8,tilex++,cell++)
  {
    int zero=0,nametabadd,ty;

    //if((cell&1)==0)
    {
      int line,vscroll;
      vscroll=Pico.vsram[(plane_sh&1)+(cell&~1)];

      // Find the line in the name table
      line=(vscroll+scan)&ts->line&0xffff; // ts->line is really ymask ..
      nametabadd=(line>>3)<<(ts->line>>24);    // .. and shift[width]
      ty=(line&7)<<1; // Y-Offset into tile
    }

    code=Pico.vram[ts->nametab+nametabadd+(tilex&ts->xmask)];
    if (code==blank) continue;
    if (code>>15) { // high priority tile
      int cval = code | (dx<<16) | (ty<<25);
      if(code&0x1000) cval^=7<<26;
      *ts->hc++ = cval; // cache it
      continue;
    }

    if (code!=oldcode) {
      oldcode = code;
      // Get tile address/2:
      addr=(code&0x7ff)<<4;
      if (code&0x1000) addr+=14-ty; else addr+=ty; // Y-flip

      pal=((code>>9)&0x30)|((plane_sh<<5)&0x40);
    }

    if (code&0x0800) zero=TileFlip(dx,addr,pal);
    else             zero=TileNorm(dx,addr,pal);

    if (zero) blank=code; // We know this tile is blank now
  }

  // terminate the cache list
  *ts->hc = 0;
  if (oldcode == -1) rendstatus |= PDRAW_PLANE_HI_PRIO;
}