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
typedef  int uint32 ;
typedef  int uint16 ;
struct TYPE_3__ {int h; } ;
struct TYPE_4__ {TYPE_1__ viewport; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_SMS ; 
 int /*<<< orphan*/  WRITE_LONG (int*,int) ; 
 int* atex_table ; 
 int /*<<< orphan*/ * bg_pattern_cache ; 
 TYPE_2__ bitmap ; 
 int /*<<< orphan*/ ** linebuf ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int* reg ; 
 scalar_t__ system_hw ; 
 int /*<<< orphan*/ * vram ; 
 int vscroll ; 

void render_bg_m4(int line, int width)
{
  int column;
  uint16 *nt;
  uint32 attr, atex, *src;
  
  /* Horizontal scrolling */
  int index = ((reg[0] & 0x40) && (line < 0x10)) ? 0x100 : reg[0x08];
  int shift = index & 7;

  /* Background line buffer */
  uint32 *dst = (uint32 *)&linebuf[0][0x20 + shift];

  /* Vertical scrolling */
  int v_line = line + vscroll;

  /* Pattern name table mask */
  uint16 nt_mask = ~0x3C00 ^ (reg[2] << 10);

  /* Unused bits used as a mask on TMS9918 & 315-5124 VDP only */
  if (system_hw > SYSTEM_SMS)
  {
    nt_mask |= 0x400;
  }

  /* Test for extended modes (Master System II & Game gear VDP only) */
  if (bitmap.viewport.h > 192)
  {
    /* Vertical scroll mask */
    v_line = v_line % 256;
    
    /* Pattern name Table */
    nt = (uint16 *)&vram[(0x3700 & nt_mask) + ((v_line >> 3) << 6)];
  }
  else
  {
    /* Vertical scroll mask */
    v_line = v_line % 224;

    /* Pattern name Table */
    nt = (uint16 *)&vram[(0x3800 + ((v_line >> 3) << 6)) & nt_mask];
  }

  /* Pattern row index */
  v_line = (v_line & 7) << 3;

  /* Tile column index */
  index = (0x100 - index) >> 3;

  /* Clip left-most column if required */
  if (shift)
  {
    memset(&linebuf[0][0x20], 0, shift);
    index++;
  }

  /* Number of tiles to draw */
  width >>= 3;

  /* Draw tiles */
  for(column = 0; column < width; column++, index++)
  {
    /* Stop vertical scrolling for rightmost eight tiles */
    if((column == 24) && (reg[0] & 0x80))
    {
      /* Clear Pattern name table start address */
      if (bitmap.viewport.h > 192)
      {
        nt = (uint16 *)&vram[(0x3700 & nt_mask) + ((line >> 3) << 6)];
      }
      else
      {
        nt = (uint16 *)&vram[(0x3800 + ((line >> 3) << 6)) & nt_mask];
      }

      /* Clear Pattern row index */
      v_line = (line & 7) << 3;
    }

    /* Read name table attribute word */
    attr = nt[index % width];
#ifndef LSB_FIRST
    attr = (((attr & 0xFF) << 8) | ((attr & 0xFF00) >> 8));
#endif

    /* Expand priority and palette bits */
    atex = atex_table[(attr >> 11) & 3];

    /* Cached pattern data line (4 bytes = 4 pixels at once) */
    src = (uint32 *)&bg_pattern_cache[((attr & 0x7FF) << 6) | (v_line)];

    /* Copy left & right half, adding the attribute bits in */
#ifdef ALIGN_DWORD
    WRITE_LONG(dst, src[0] | atex);
    dst++;
    WRITE_LONG(dst, src[1] | atex);
    dst++;
#else
    *dst++ = (src[0] | atex);
    *dst++ = (src[1] | atex);
#endif
  }
}