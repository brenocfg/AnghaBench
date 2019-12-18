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
struct TYPE_2__ {scalar_t__ vram; struct PicoVideo video; } ;

/* Variables and functions */
 TYPE_1__ Pico ; 
 int /*<<< orphan*/  TileNormM4 (unsigned int,unsigned int,int) ; 

__attribute__((used)) static void draw_sprites(int scanline)
{
  struct PicoVideo *pv = &Pico.video;
  unsigned int sprites_addr[8];
  unsigned int sprites_x[8];
  unsigned char *sat;
  int xoff = 8; // relative to HighCol, which is (screen - 8)
  int sprite_base, addr_mask;
  int i, s, h;

  if (pv->reg[0] & 8)
    xoff = 0;

  sat = (unsigned char *)Pico.vram + ((pv->reg[5] & 0x7e) << 7);
  if (pv->reg[1] & 2) {
    addr_mask = 0xfe; h = 16;
  } else {
    addr_mask = 0xff; h = 8;
  }
  sprite_base = (pv->reg[6] & 4) << (13-2-1);

  for (i = s = 0; i < 64 && s < 8; i++)
  {
    int y;
    y = sat[i] + 1;
    if (y == 0xd1)
      break;
    if (y + h <= scanline || scanline < y)
      continue; // not on this line

    sprites_x[s] = xoff + sat[0x80 + i*2];
    sprites_addr[s] = sprite_base + ((sat[0x80 + i*2 + 1] & addr_mask) << (5-1)) +
      ((scanline - y) << (2-1));
    s++;
  }

  // now draw all sprites backwards
  for (--s; s >= 0; s--)
    TileNormM4(sprites_x[s], sprites_addr[s], 0x10);
}