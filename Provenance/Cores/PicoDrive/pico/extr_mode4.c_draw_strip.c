#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int TileFlipM4 (int,int,int) ; 
 int TileNormM4 (int,int,int) ; 

__attribute__((used)) static void draw_strip(const unsigned short *nametab, int dx, int cells, int tilex_ty_prio)
{
  int oldcode = -1, blank = -1; // The tile we know is blank
  int addr = 0, pal = 0;

  // Draw tiles across screen:
  for (; cells > 0; dx += 8, tilex_ty_prio++, cells--)
  {
    int code, zero;

    code = nametab[tilex_ty_prio & 0x1f];
    if (code == blank)
      continue;
    if ((code ^ tilex_ty_prio) & 0x1000) // priority differs?
      continue;

    if (code != oldcode) {
      oldcode = code;
      // Get tile address/2:
      addr = (code & 0x1ff) << 4;
      addr += tilex_ty_prio >> 16;
      if (code & 0x0400)
        addr ^= 0xe; // Y-flip

      pal = (code>>7) & 0x10;
    }

    if (code&0x0200) zero = TileFlipM4(dx, addr, pal);
    else             zero = TileNormM4(dx, addr, pal);

    if (zero)
      blank = code; // We know this tile is blank now
  }
}