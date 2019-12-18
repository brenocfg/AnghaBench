#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint16 ;
struct TYPE_5__ {int h; scalar_t__ x; } ;
struct TYPE_8__ {TYPE_1__ viewport; } ;
struct TYPE_7__ {int /*<<< orphan*/  gg_extra; } ;
struct TYPE_6__ {int xpos; int size; int attr; int ypos; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_GG ; 
 TYPE_4__ bitmap ; 
 TYPE_3__ config ; 
 int** linebuf ; 
 int** lut ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int object_count ; 
 TYPE_2__* object_info ; 
 int* reg ; 
 int spr_ovr ; 
 int status ; 
 scalar_t__ system_hw ; 
 int v_counter ; 
 int /*<<< orphan*/ * vram ; 

void render_obj_tms(int max_width)
{
  int x, count, start, end;
  uint8 *lb, *sg;
  uint8 color, pattern[2];
  uint16 temp;

  /* Default sprite width (8 pixels) */
  int width = 8;

  /* Adjust width for 16x16 sprites */
  width <<= ((reg[1] & 0x02) >> 1);

  /* Adjust width for zoomed sprites */
  width <<= (reg[1] & 0x01);

  /* Set SOVR flag */
  status |= spr_ovr;
  spr_ovr = 0;

  /* Draw sprites in front-to-back order */
  for (count = 0; count < object_count; count++)
  {
    /* Sprite X position */
    start = object_info[count].xpos;

    /* Sprite Color + Early Clock bit */
    color = object_info[count].size;

    /* X position shift (32 pixels) */
    start -= ((color & 0x80) >> 2);

    /* Pointer to line buffer */
    lb = &linebuf[0][0x20 + start];

    if ((start + width) > 256)
    {
      /* Clip sprites on right edge */
      end = 256 - start;

      start = 0;
    }
    else
    {
      end = width;

      if (start < 0)
      {
        /* Clip sprites on left edge */
        start = 0 - start;
      }
      else
      {
        start = 0;
      }
    }

    /* Sprite Color (0-15) */
    color &= 0x0F;

    /* Sprite Pattern Name */
    temp = object_info[count].attr;

    /* Mask two LSB for 16x16 sprites */
    temp &= ~((reg[1] & 0x02) >> 0);
    temp &= ~((reg[1] & 0x02) >> 1);

    /* Pointer to sprite generator table */
    sg = (uint8 *)&vram[((reg[6] << 11) & 0x3800) | (temp << 3) | object_info[count].ypos];

    /* Sprite Pattern data (2 x 8 pixels) */
    pattern[0] = sg[0x00];
    pattern[1] = sg[0x10];

    if (reg[1] & 0x01)
    {
      /* Zoomed sprites are rendered at half speed */
      for (x=start; x<end; x+=2)
      {
        temp = pattern[(x >> 4) & 1];
        temp = (temp >> (7 - ((x >> 1) & 7))) & 0x01;
        temp = temp * color;
        temp |= (lb[x] << 8);
        lb[x] = lut[5][temp];
        status |= ((temp & 0x8000) >> 10);
        temp &= 0x00FF;
        temp |= (lb[x+1] << 8);
        lb[x+1] = lut[5][temp];
        status |= ((temp & 0x8000) >> 10);
      }
    }
    else
    {
      /* Normal sprites */
      for (x=start; x<end; x++)
      {
        temp = pattern[(x >> 3) & 1];
        temp = (temp >> (7 - (x & 7))) & 0x01;
        temp = temp * color;
        temp |= (lb[x] << 8);
        lb[x] = lut[5][temp];
        status |= ((temp & 0x8000) >> 10);
      }
    }
  }

  /* handle Game Gear reduced screen (160x144) */
  if ((system_hw == SYSTEM_GG) && !config.gg_extra && (v_counter < bitmap.viewport.h))
  {
    int line = v_counter - (bitmap.viewport.h - 144) / 2;
    if ((line < 0) || (line >= 144))
    {
      memset(&linebuf[0][0x20], 0x40, max_width);
    }
    else
    {
      if (bitmap.viewport.x > 0)
      {
        memset(&linebuf[0][0x20], 0x40, 48);
        memset(&linebuf[0][0x20+48+160], 0x40, 48);
      }
    }
  }
}