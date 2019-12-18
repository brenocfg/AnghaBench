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
struct TYPE_5__ {scalar_t__ dirtyPal; } ;
struct TYPE_4__ {int* reg; } ;
struct TYPE_6__ {TYPE_2__ m; TYPE_1__ video; } ;

/* Variables and functions */
 unsigned short* DrawLineDest ; 
 scalar_t__ DrawLineDestBase ; 
 int DrawLineDestIncrement ; 
 unsigned short* HighPal ; 
 TYPE_3__ Pico ; 
 unsigned char* PicoDraw2FB ; 
 int /*<<< orphan*/  PicoDrawUpdateHighPal () ; 
 int /*<<< orphan*/  PicoScan32xBegin (int) ; 
 int /*<<< orphan*/  PicoScan32xEnd (int) ; 

void PicoDraw32xLayerMdOnly(int offs, int lines)
{
  int have_scan = PicoScan32xBegin != NULL && PicoScan32xEnd != NULL;
  unsigned short *dst = (void *)((char *)DrawLineDestBase + offs * DrawLineDestIncrement);
  unsigned char  *pmd = PicoDraw2FB + 328 * offs + 8;
  unsigned short *pal = HighPal;
  int poffs = 0, plen = 320;
  int l, p;

  if (!(Pico.video.reg[12] & 1)) {
    // 32col mode
    poffs = 32;
    plen = 256;
  }

  if (Pico.m.dirtyPal)
    PicoDrawUpdateHighPal();

  dst += poffs;
  for (l = 0; l < lines; l++) {
    if (have_scan) {
      PicoScan32xBegin(l + offs);
      dst = DrawLineDest + poffs;
    }
    for (p = 0; p < plen; p += 4) {
      dst[p + 0] = pal[*pmd++];
      dst[p + 1] = pal[*pmd++];
      dst[p + 2] = pal[*pmd++];
      dst[p + 3] = pal[*pmd++];
    }
    dst = (void *)((char *)dst + DrawLineDestIncrement);
    pmd += 328 - plen;
    if (have_scan)
      PicoScan32xEnd(l + offs);
  }
}