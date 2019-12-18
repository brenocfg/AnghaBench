#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* reg; } ;
struct TYPE_4__ {scalar_t__ dirtyPal; } ;
struct TYPE_6__ {TYPE_2__ video; TYPE_1__ m; } ;

/* Variables and functions */
 unsigned short* DrawLineDest ; 
 unsigned char* HighCol ; 
 unsigned short* HighPal ; 
 int PDRAW_SPR_LO_ON_HI ; 
 int POPT_DIS_32C_BORDER ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  PicoDoHighPal555 (int) ; 
 int PicoOpt ; 
 int rendstatus ; 

void FinalizeLine555(int sh, int line)
{
  unsigned short *pd=DrawLineDest;
  unsigned char  *ps=HighCol+8;
  unsigned short *pal=HighPal;
  int len;

  if (Pico.m.dirtyPal)
    PicoDoHighPal555(sh);

  if (Pico.video.reg[12]&1) {
    len = 320;
  } else {
    if (!(PicoOpt&POPT_DIS_32C_BORDER)) pd+=32;
    len = 256;
  }

  {
#ifndef PSP
    int i, mask=0xff;
    if (!sh && (rendstatus & PDRAW_SPR_LO_ON_HI))
      mask=0x3f; // accurate sprites, upper bits are priority stuff

    for (i = 0; i < len; i++)
      pd[i] = pal[ps[i] & mask];
#else
    extern void amips_clut(unsigned short *dst, unsigned char *src, unsigned short *pal, int count);
    extern void amips_clut_6bit(unsigned short *dst, unsigned char *src, unsigned short *pal, int count);
    if (!sh && (rendstatus & PDRAW_SPR_LO_ON_HI))
         amips_clut_6bit(pd, ps, pal, len);
    else amips_clut(pd, ps, pal, len);
#endif
  }
}