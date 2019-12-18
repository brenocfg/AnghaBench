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
typedef  int uint16 ;
struct TYPE_2__ {int attr; int xpos; int ypos; int size; } ;

/* Variables and functions */
 int im2_flag ; 
 int object_count ; 
 TYPE_1__* object_info ; 
 int* reg ; 
 int /*<<< orphan*/ * sat ; 
 size_t satb ; 
 int status ; 
 int /*<<< orphan*/ * vram ; 

void parse_satb_m5(int line)
{
  /* Y position */
  int ypos;

  /* Sprite height (8,16,24,32 pixels)*/
  int height;

  /* Sprite size data */
  int size;

  /* Sprite link data */
  int link = 0;

  /* Sprite counter */
  int count = 0;

  /* 16 or 20 sprites max. per line */
  int max = 16 + ((reg[12] & 1) << 2);

  /* 64 or 80 sprites max. */
  int total = max << 2;

  /* Pointer to sprite attribute table */
  uint16 *p = (uint16 *) &vram[satb];

  /* Pointer to internal RAM */
  uint16 *q = (uint16 *) &sat[0];

  /* Adjust line offset */
  line += 0x81;

  do
  {
    /* Read Y position & size from internal SAT */
    ypos = (q[link] >> im2_flag) & 0x1FF;
    size = q[link + 1] >> 8;

    /* Sprite height */
    height = 8 + ((size & 3) << 3);

    /* Y range */
    ypos = line - ypos;

    /* Sprite is visble on this line ? */
    if ((ypos >= 0) && (ypos < height))
    {
      /* Sprite overflow */
      if (count == max)
      {
        status |= 0x40;
        break;
      }

      /* Update sprite list */
      /* name, attribute & xpos are parsed from VRAM */ 
      object_info[count].attr  = p[link + 2];
      object_info[count].xpos  = p[link + 3] & 0x1ff;
      object_info[count].ypos  = ypos;
      object_info[count].size  = size & 0x0f;
      ++count;
    }

    /* Read link data from internal SAT */ 
    link = (q[link + 1] & 0x7F) << 2;

    /* Last sprite */
    if (link == 0) break;
  }
  while (--total);

  /* Update sprite count for next line */
  object_count = count;
}