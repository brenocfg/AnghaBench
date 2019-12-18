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
typedef  void* uint8 ;
typedef  int uint16 ;
struct TYPE_4__ {int h; } ;
struct TYPE_6__ {TYPE_1__ viewport; } ;
struct TYPE_5__ {int ypos; void* attr; void* xpos; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_MD ; 
 scalar_t__ SYSTEM_SMS ; 
 TYPE_3__ bitmap ; 
 int object_count ; 
 TYPE_2__* object_info ; 
 int* reg ; 
 int spr_ovr ; 
 scalar_t__ system_hw ; 
 void** vram ; 

void parse_satb_m4(int line)
{
  int i = 0;
  uint8 *st;

  /* Sprite counter (8 max. per line) */
  int count = 0;

  /* Y position */
  int ypos;

  /* Sprite height (8x8 or 8x16) */
  int height = 8 + ((reg[1] & 0x02) << 2);

  /* Sprite attribute table address mask */
  uint16 st_mask = ~0x3F80 ^ (reg[5] << 7);

  /* Unused bits used as a mask on 315-5124 VDP only */
  if (system_hw > SYSTEM_SMS)
  {
    st_mask |= 0x80;
  }

  /* Pointer to sprite attribute table */
  st = &vram[st_mask & 0x3F00];

  /* Parse Sprite Table (64 entries) */
  do
  {
    /* Sprite Y position */
    ypos = st[i];

    /* Check end of sprite list marker */
    if (ypos == (bitmap.viewport.h + 16))
    {
      break;
    }

    /* Wrap Y coordinate for sprites > 256-16 */
    if (ypos >= 240)
    {
      ypos -= 256;
    }

    /* Y range */
    ypos = line - ypos;

    /* Adjust Y range for zoomed sprites (not working on Mega Drive VDP) */
    if (system_hw < SYSTEM_MD)
    {
      ypos >>= (reg[1] & 0x01);
    }

    /* Check if sprite is visible on this line */
    if ((ypos >= 0) && (ypos < height))
    {
      /* Sprite overflow */
      if (count == 8)
      {
        /* Flag is set only during active area */
        if ((line >= 0) && (line < bitmap.viewport.h))
        {
          spr_ovr = 0x40;
        }
        break;
      }

      /* Store sprite attributes for later processing */
      object_info[count].ypos = ypos;
      object_info[count].xpos = st[(0x80 + (i << 1)) & st_mask];
      object_info[count].attr = st[(0x81 + (i << 1)) & st_mask];

      /* Increment Sprite count */
      ++count;
    }
  }
  while (++i < 64);

  /* Update sprite count for next line */
  object_count = count;
}