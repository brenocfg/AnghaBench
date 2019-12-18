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
struct TYPE_4__ {int h; } ;
struct TYPE_6__ {TYPE_1__ viewport; } ;
struct TYPE_5__ {int ypos; void* size; void* attr; void* xpos; } ;

/* Variables and functions */
 TYPE_3__ bitmap ; 
 int object_count ; 
 TYPE_2__* object_info ; 
 int* reg ; 
 int spr_ovr ; 
 int status ; 
 void** vram ; 

void parse_satb_tms(int line)
{
  int i = 0;

  /* Sprite counter (4 max. per line) */
  int count = 0;

  /* no sprites in Text modes */
  if (!(reg[1] & 0x10))
  {
    /* Pointer to sprite attribute table */
    uint8 *st = &vram[(reg[5] << 7) & 0x3F80];

    /* Y position */
    int ypos;

    /* Sprite height (8 pixels by default) */
    int height = 8;

    /* Adjust height for 16x16 sprites */
    height <<= ((reg[1] & 0x02) >> 1);

    /* Adjust height for zoomed sprites */
    height <<= (reg[1] & 0x01);

    /* Parse Sprite Table (32 entries) */
    do
    {
      /* Sprite Y position */
      ypos = st[i << 2];

      /* Check end of sprite list marker */
      if (ypos == 0xD0)
      {
        break;
      }

      /* Wrap Y coordinate for sprites > 256-32 */
      if (ypos >= 224)
      {
        ypos -= 256;
      }

      /* Y range */
      ypos = line - ypos;

      /* Sprite is visble on this line ? */
      if ((ypos >= 0) && (ypos < height))
      {
        /* Sprite overflow */
        if (count == 4)
        {
          /* Flag is set only during active area */
          if (line < bitmap.viewport.h)
          {
            spr_ovr = 0x40;
          }
          break;
        }

        /* Adjust Y range back for zoomed sprites */
        ypos >>= (reg[1] & 0x01);

        /* Store sprite attributes for later processing */
        object_info[count].ypos = ypos;
        object_info[count].xpos = st[(i << 2) + 1];
        object_info[count].attr = st[(i << 2) + 2];
        object_info[count].size = st[(i << 2) + 3];

        /* Increment Sprite count */
        ++count;
      }
    }
    while (++i < 32);
  }

  /* Update sprite count for next line */
  object_count = count;

  /* Insert number of last sprite entry processed */
  status = (status & 0xE0) | (i & 0x1F);
}