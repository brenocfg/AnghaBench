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
typedef  int uint8 ;
typedef  int uint16 ;

/* Variables and functions */
 scalar_t__ SYSTEM_SMS ; 
 int** linebuf ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int* reg ; 
 scalar_t__ system_hw ; 
 int* vram ; 

void render_bg_m1x(int line, int width)
{
  uint8 pattern;
  uint8 *pg;

  uint8 color = reg[7];

  uint8 *lb = &linebuf[0][0x20];
  uint8 *nt = &vram[((reg[2] << 10) & 0x3C00) + ((line >> 3) * 40)];

  uint16 pg_mask = ~0x3800 ^ (reg[4] << 11);

  /* Unused bits used as a mask on TMS9918 & 315-5124 VDP only */
  if (system_hw > SYSTEM_SMS)
  {
    pg_mask |= 0x1800;
  }

  pg = &vram[((0x2000 + ((line & 0xC0) << 5)) & pg_mask) + (line & 7)];

  /* Left border (8 pixels) */
  memset (lb, 0x40, 8);
  lb += 8;

  /* 40 x 6 pixels */
  width = 40;

  do
  {
    pattern = pg[*nt++ << 3];

    *lb++ = 0x10 | ((color >> (((pattern >> 7) & 1) << 2)) & 0x0F);
    *lb++ = 0x10 | ((color >> (((pattern >> 6) & 1) << 2)) & 0x0F);
    *lb++ = 0x10 | ((color >> (((pattern >> 5) & 1) << 2)) & 0x0F);
    *lb++ = 0x10 | ((color >> (((pattern >> 4) & 1) << 2)) & 0x0F);
    *lb++ = 0x10 | ((color >> (((pattern >> 3) & 1) << 2)) & 0x0F);
    *lb++ = 0x10 | ((color >> (((pattern >> 2) & 1) << 2)) & 0x0F);
  }
  while (--width);

  /* Right borders (8 pixels) */
  memset(lb, 0x40, 8);
}