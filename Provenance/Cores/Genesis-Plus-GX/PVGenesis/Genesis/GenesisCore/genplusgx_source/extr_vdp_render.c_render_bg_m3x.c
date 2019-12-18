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
 int* reg ; 
 scalar_t__ system_hw ; 
 int* vram ; 

void render_bg_m3x(int line, int width)
{
  uint8 color;
  uint16 name;
  uint8 *pg;

  uint8 *lb = &linebuf[0][0x20];
  uint8 *nt = &vram[((reg[2] << 10) & 0x3C00) + ((line & 0xF8) << 2)];

  uint16 pg_mask = ~0x3800 ^ (reg[4] << 11);

  /* Unused bits used as a mask on TMS9918 & 315-5124 VDP only */
  if (system_hw > SYSTEM_SMS)
  {
    pg_mask |= 0x1800;
  }

  pg = &vram[((0x2000 + ((line & 0xC0) << 5)) & pg_mask) + ((line >> 2) & 7)];

  /* 32 x 8 pixels */
  width = 32;

  do
  {
    name = *nt++;
    color = pg[name << 3];
    
    *lb++ = 0x10 | ((color >> 4) & 0x0F);
    *lb++ = 0x10 | ((color >> 4) & 0x0F);
    *lb++ = 0x10 | ((color >> 4) & 0x0F);
    *lb++ = 0x10 | ((color >> 4) & 0x0F);
    *lb++ = 0x10 | ((color >> 0) & 0x0F);
    *lb++ = 0x10 | ((color >> 0) & 0x0F);
    *lb++ = 0x10 | ((color >> 0) & 0x0F);
    *lb++ = 0x10 | ((color >> 0) & 0x0F);
  }
  while (--width);
}