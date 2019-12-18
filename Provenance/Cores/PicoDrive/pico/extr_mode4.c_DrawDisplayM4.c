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
struct TYPE_2__ {unsigned short* vram; struct PicoVideo video; } ;

/* Variables and functions */
 scalar_t__ HighCol ; 
 int PDRAW_LAYERA_ON ; 
 int PDRAW_LAYERB_ON ; 
 int PDRAW_SPRITES_LOW_ON ; 
 TYPE_1__ Pico ; 
 int PicoDrawMask ; 
 int /*<<< orphan*/  draw_sprites (int) ; 
 int /*<<< orphan*/  draw_strip (unsigned short*,int,int,int) ; 

__attribute__((used)) static void DrawDisplayM4(int scanline)
{
  struct PicoVideo *pv = &Pico.video;
  unsigned short *nametab;
  int line, tilex, dx, ty, cells;
  int cellskip = 0; // XXX
  int maxcells = 32;

  // Find the line in the name table
  line = pv->reg[9] + scanline; // vscroll + scanline
  if (line >= 224)
    line -= 224;

  // Find name table:
  nametab = Pico.vram;
  nametab += (pv->reg[2] & 0x0e) << (10-1);
  nametab += (line>>3) << (6-1);

  dx = pv->reg[8]; // hscroll
  if (scanline < 16 && (pv->reg[0] & 0x40))
    dx = 0; // hscroll disabled for top 2 rows

  tilex = ((-dx >> 3) + cellskip) & 0x1f;
  ty = (line & 7) << 1; // Y-Offset into tile
  cells = maxcells - cellskip;

  dx = ((dx - 1) & 7) + 1;
  if (dx != 8)
    cells++; // have hscroll, need to draw 1 cell more
  dx += cellskip << 3;

  // low priority tiles
  if (PicoDrawMask & PDRAW_LAYERB_ON)
    draw_strip(nametab, dx, cells, tilex | 0x0000 | (ty << 16));

  // sprites
  if (PicoDrawMask & PDRAW_SPRITES_LOW_ON)
    draw_sprites(scanline);

  // high priority tiles (use virtual layer switch just for fun)
  if (PicoDrawMask & PDRAW_LAYERA_ON)
    draw_strip(nametab, dx, cells, tilex | 0x1000 | (ty << 16));

  if (pv->reg[0] & 0x20)
    // first column masked
    ((int *)HighCol)[2] = ((int *)HighCol)[3] = 0xe0e0e0e0;
}